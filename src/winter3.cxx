#include "winter3.h"
#include "csv.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <filesystem>
#include <numeric>
#include <TCanvas.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TF1.h>
#include <TLegend.h>

using namespace std;
using namespace csv;
namespace fs = filesystem;

int extractYearWint(const string& date) {
    return stoi(date.substr(0, 4));
}


// Process temperature data from the CSV
void winterParse(const string& filename, vector<int>& years, vector<double>& avgTemperatures) {
    CSVReader readerWint(filename);

    map<int, vector<double>> winterMap;

    int rowCount = 0;
    for (auto row : readerWint) {
        rowCount++;

        string date_str = row[0].get<string>();   // Get date (YYYY-MM-DD)
        double temperature = row[2].get<double>();   // Get temperature

        int year = extractYearWint(date_str); // Extract just the year

        winterMap[year].push_back(temperature);
    }
    for (auto& entry : winterMap) {
        years.push_back(entry.first);
        const vector<double>& temps = entry.second;

        double tempSum = accumulate(temps.begin(), temps.end(), 0.0);
        double avgTemp = tempSum/temps.size();
        avgTemperatures.push_back(avgTemp);
    }
    //For debugging
    //int n = years.size();
    //for (int i = 0; i < n; ++i){
    //    cout << "Year: " << years[i] << " Temp: " << avgTemperatures[i] << endl;}
    

        
    
}

/*
void calculateYearlyAverages() {
    for (const auto& entry : year_to_temperatures) {
        int year = entry.first;
        const vector<double>& temps = entry.second;

        // Calculate the average temperature for the year
        double sum = 0;
        for (double temp : temps) {
            sum += temp;
        }
        double average_temp = sum / temps.size();  // Calculate the average
        yearly_avg_temperatures[year] = average_temp;  // Store the average temperature
    }
}
*/
void plotWinter(vector<int>& years, vector<double>& avgTemps){
    int n = years.size();

    double minAvgTemp = *min_element(avgTemps.begin(), avgTemps.end());
    double maxAvgTemp = *max_element(avgTemps.begin(), avgTemps.end());

    auto winterCanvas = new TCanvas("winter_canvas","Winter Temperatures by Year", 1200, 600);
    auto winterGraph = new TGraph(n);
    for (int i = 0; i < n; ++i){
        winterGraph->SetPoint(i, years[i], avgTemps[i]);
    }
    winterGraph->SetLineColor(kRed);
    winterGraph->GetYaxis()->SetRangeUser(minAvgTemp - 5, maxAvgTemp + 5);

    winterGraph->GetYaxis()->SetTitle("Temperature [degrees C]");
    winterGraph->GetXaxis()->SetTitle("Year");
    
    winterGraph->GetXaxis()->CenterTitle();
    winterGraph->GetYaxis()->CenterTitle();

    winterGraph->Draw();

    TF1 *linearFit = new TF1("linearFit", "pol1", years[0], years[n-1]);
    linearFit->SetLineColor(kBlack);
    linearFit->SetLineWidth(2);

    auto winterLegend = new TLegend(0.7,0.8,0.9,0.9);
    winterLegend->AddEntry(winterGraph, "Avg Winter Temperatures", "lp");
    winterLegend->AddEntry(linearFit, "Linear Fit", "lp");
    winterLegend->SetTextSize(0.02);
    winterLegend->Draw();

    winterGraph->Fit(linearFit, "R");
    winterCanvas->Update();
    winterCanvas->SaveAs("winter_temps.png");
}
int getWinter(string filePath){
    string filePathName = std::filesystem::path(filePath).filename().string();
    string filename = "Winter_filtered_" + filePathName;

    vector<int> years;
    vector<double> avgTemperatures;

    winterParse(filename, years, avgTemperatures);
    plotWinter(years, avgTemperatures);

    return 0;
}