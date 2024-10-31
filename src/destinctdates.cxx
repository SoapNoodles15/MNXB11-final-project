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


#include "csv.hpp"
using namespace std;

using namespace csv;

int Year(const string& date1) {
    return stoi(date1.substr(0, 4));
}

int MakeColumns(const string filename, vector<int>& years, vector<double>& temp) {
    CSVReader reader(filename);
 

    //vector<string> date;
    //vector<double> temp;



    for (CSVRow& row : reader) {
        // Add values from the specified columns (by index) to the vectors
        //date.push_back(row[0].get<string>());
        int year = Year(row[0].get<string>());
        years.push_back(year);
        temp.push_back(row[2].get<double>());

    }

    return 0;
}

void makehist(vector<double>& april, vector<double>& june, vector<double>& september, vector<double>& december){
     
    auto Canvas = new TCanvas("canvas", "april histogram", 800, 600);
    
    auto spring = new TH1F("april", "something", 100,-30,40);
    auto summer = new TH1F("june", "something", 100,-30,40);
    auto fall = new TH1F("september", "something", 100, -30, 40);
    auto winter = new TH1F("december", "something", 100, -30, 40);

    for(double temp : april){
        spring->Fill(temp);
    }
    for(double temp : june){
        summer->Fill(temp);
    }
    for(double temp : september){
        fall->Fill(temp);
    }
    for(double temp : december){
        winter->Fill(temp);
    }
    spring->SetFillColor(kGreen +2);
    spring->SetFillStyle(3004);
    spring->SetLineColor(kGreen +2);

    summer->SetFillColor(kBlue +2);
    summer->SetFillStyle(3005);
    summer->SetLineColor(kBlue +2);

    fall->SetFillColor(kBlack);
    fall->SetFillStyle(3007);
    fall->SetLineColor(kBlack);

    winter->SetFillColor(kRed +2);
    winter->SetFillStyle(3005);
    winter->SetLineColor(kRed +2);

    spring->Draw();
    summer->Draw("SAME");
    fall->Draw("SAME");
    winter->Draw("SAME");
    
    Canvas->Update();
    Canvas->SaveAs("plot.png");

}



int getFourDates(string filename) {
    string filePathName = std::filesystem::path(filename).filename().string();
    string april = "03April_filtered_" + filePathName;
    string june = "26June_filtered_" + filePathName;
    string september = "29September_filtered_" + filePathName;
    string december = "24December_filtered_" + filePathName;


   
    vector<double> tempApril;
    vector<double> tempJune;
    vector<double> tempSeptember;
    vector<double> tempDecember;

    vector<int> dateApril;
    vector<int> dateJune;
    vector<int> dateSeptember;
    vector<int> dateDecember;

    MakeColumns(april, dateApril, tempApril);
    MakeColumns(june, dateJune, tempJune);
    MakeColumns(september,dateSeptember, tempSeptember);
    MakeColumns(december, dateDecember, tempDecember);

    // cout << "Dates and Temperatures:" << endl;
    // for (size_t i = 0; i < dateApril.size(); ++i) {
        // cout << "Date: " << dateApril[i] << ", Temperature: " << tempApril[i] << endl;
        // cout << "Date: " << dateJune[i] << ", Temperature: " << tempJune[i] << endl;
        // cout << "Date: " << dateSeptember[i] << ", Temperature: " << tempSeptember[i] << endl;
        // cout << "Date: " << dateDecember[i] << ", Temperature: " << tempDecember[i] << endl;


    // }
    makehist(tempApril,tempJune,tempSeptember,tempDecember);
    
    
   

    return 0;

}

