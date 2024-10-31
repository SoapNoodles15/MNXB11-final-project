#include "csv.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <filesystem>
#include <TCanvas.h>
#include <TGraph.h>
#include <TLegend.h>
#include <TAxis.h>
#include <algorithm>
#include <TH1F.h>


using namespace std;
using namespace csv;

// Extracting the year from the date string
int extractYear(const string& date) {
    return stoi(date.substr(0, 4));
}

// Function to parse through the CSV file
void parseCSV(const string& filename, vector<int>& years, vector<double>& coldTemps, vector<double>& warmTemps) {
    CSVFormat format; // Specifying the data format
    format.delimiter(','); 
    format.no_header();

    try {
        CSVReader reader(filename, format);  // Initializing CSVReader with filename and the desired format
        
        map<int, double> coldTempsMap; // Maps used to store the coldest and warmest temperatures for each year
        map<int, double> warmTempsMap;
        
        cout << "Reading CSV file: " << filename << endl;

        int rowCount = 0;  // Row count for debugging purposes
        for (auto& row : reader) {
            rowCount++;  // Incrementing the row count on each iteration

            // Accessing columns by index 
            if (!row[0].is_null() && !row[2].is_null()) { // If date is NOT null AND temp is NOT null
                string date = row[0].get<string>();  // Extracting date 
                double temperature = row[2].get<double>();  // Extracting temperature

                int year = extractYear(date);  // Getting the year from date
                
                if (coldTempsMap.find(year) == coldTempsMap.end() || temperature < coldTempsMap[year]) { // Checking if there is a temp for a year and comparing
                    coldTempsMap[year] = temperature; // Updating coldest temperature
                }

                if (warmTempsMap.find(year) == warmTempsMap.end() || temperature > warmTempsMap[year]) { 
                    warmTempsMap[year] = temperature; // Updating warmest temperature
                }
            } else {
                cout << "Row " << rowCount << ": Skipping empty or malformed row" << endl; 
            }
        }

        cout << "Total rows processed: " << rowCount << endl; 

        // Clearing the vectors
        years.clear();
        coldTemps.clear();
        warmTemps.clear();

        // Transfering the data from maps to vectors
        for (auto& entry : coldTempsMap) {
            years.push_back(entry.first);
            coldTemps.push_back(entry.second);
            warmTemps.push_back(warmTempsMap[entry.first]);
        }

    } catch (const exception& e) {
        cerr << "Error reading CSV file: " << e.what() << endl; 
    }
}

// A function used to plot with ROOT
void plotColdWarm(vector<double>& coldTemps, vector<double>& warmTemps) {

    double coldMin = *min_element(coldTemps.begin(), coldTemps.end());
    double coldMax = *max_element(coldTemps.begin(), coldTemps.end());
    double warmMin = *min_element(warmTemps.begin(), warmTemps.end());
    double warmMax = *max_element(warmTemps.begin(), warmTemps.end());
    /*
    int n = years.size();
    


    int yearMin = years[0];
    int yearMax = years.back();

    
    auto coldCanvas = new TCanvas("canvas1", "Coldest Temperatures by Year", 800, 600);
    auto coldGraph = new TGraph(n);
    for (int i=0; i < n; ++i) {
        coldGraph->SetPoint(i, years[i], coldTemps[i]);
    }
    coldCanvas->SetGrid();
    coldGraph->SetMarkerColor(kBlue);
    coldGraph->SetMarkerSize(1.5);
    coldGraph->GetYaxis()->SetRangeUser(coldMin - 5, coldMax + 5);
    coldGraph->GetXaxis()->SetRangeUser(yearMin, yearMax);
    coldGraph->SetLineColor(kBlue+2);
    coldGraph->Draw("");


    auto coldLegend = new TLegend(0.7, 0.5, 0.9, 0.7);
    coldLegend->SetTextSize(0.03);
    coldLegend->AddEntry(coldGraph, "Coldest Temperatures", "lp");
    coldLegend->Draw();

    coldCanvas->Update();
    coldCanvas->SaveAs("cold_temp.png");



    auto warmCanvas = new TCanvas("canvas2", "Warmest Temperatures by Year", 800, 600);
    auto warmGraph = new TGraph(n);
    for (int i=0; i < n; ++i) {
        warmGraph->SetPoint(i, years[i], warmTemps[i]);
    }
    warmCanvas->SetGrid();
    warmGraph->SetMarkerColor(kRed+2);
    //warmGraph->SetLineColor(kRed);
    warmGraph->SetMarkerSize(1.5);
    warmGraph->GetYaxis()->SetRangeUser(warmMin - 5, warmMax + 5);
    warmGraph->GetXaxis()->SetRangeUser(yearMin, yearMax);
    warmGraph->Draw();

    auto warmLegend = new TLegend(0.7, 0.5, 0.9, 0.7);
    warmLegend->SetTextSize(0.03);
    warmLegend->AddEntry(warmGraph, "Warmest Temperatures", "lp");
    warmLegend->Draw();

    warmCanvas->Update();
    warmCanvas->SaveAs("warm_temp.png");



    */
    auto coldHistCanvas = new TCanvas("canvas3", "Coldest Temperatures Histogram", 800, 600);
    auto coldHist = new TH1F("Stats", "Coldest Temperatures Histogram", 100, coldMin - 5, coldMax + 5);
    for (double temp : coldTemps) {
        coldHist->Fill(temp);
    }
    coldHist->SetFillColor(kBlue+2);
    coldHist->SetLineColor(kBlack);
    coldHist->GetYaxis()->SetTitle("Count");
    coldHist->GetXaxis()->SetTitle("Temperature");
    coldHist->GetYaxis()->CenterTitle();
    coldHist->GetXaxis()->CenterTitle();
    coldHist->Draw();
    coldHistCanvas->Update();
    coldHistCanvas->SaveAs("cold_hist.png");

    auto warmHistCanvas = new TCanvas("canvas4", "Warmest Temperatures Histogram", 800, 600);
    auto warmHist = new TH1F("Stats", "Warmest Temperatures Histogram", 100, warmMin - 5, warmMax + 5);
    for (double temp : warmTemps) {
        warmHist->Fill(temp);
    }
    warmHist->SetFillColor(kRed+2);
    warmHist->SetLineColor(kBlack);
    warmHist->GetYaxis()->SetTitle("Count");
    warmHist->GetXaxis()->SetTitle("Temperature");
    warmHist->GetYaxis()->CenterTitle();
    warmHist->GetXaxis()->CenterTitle();
    warmHist->Draw();
    warmHistCanvas->Update();
    warmHistCanvas->SaveAs("warm_hist.png");
}




// A function to actually obtain the data and plot it
int getColdWarm(string filePath) {
    string filePathName = std::filesystem::path(filePath).filename().string(); // Get the original file name
    string filename = "ColdestWarmest_filtered_" + filePathName; // Get the file name with the desired data after pre-processing

    vector<int> years; // Initialize the data vectors
    vector<double> coldestTemps;
    vector<double> warmestTemps;

    parseCSV(filename, years, coldestTemps, warmestTemps); // Parse the CSV to fill those vectors

    plotColdWarm(coldestTemps, warmestTemps); // Plot them
    /*
    // Printing out the years and temperatures
    cout << "Years and Temperatures:" << endl;
    for (size_t i = 0; i < years.size(); i++) {
        cout << "Year: " << years[i] << ", Coldest Temp: " << coldestTemps[i] << ", Warmest Temp: " << warmestTemps[i] << endl;
    }
    */
    return 0;
}
