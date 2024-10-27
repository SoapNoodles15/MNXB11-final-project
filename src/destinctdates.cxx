#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>

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

    cout << "Dates and Temperatures:" << endl;
    for (size_t i = 0; i < dateApril.size(); ++i) {
        cout << "Date: " << dateApril[i] << ", Temperature: " << tempApril[i] << endl;
        cout << "Date: " << dateJune[i] << ", Temperature: " << tempJune[i] << endl;
        cout << "Date: " << dateSeptember[i] << ", Temperature: " << tempSeptember[i] << endl;
        cout << "Date: " << dateDecember[i] << ", Temperature: " << tempDecember[i] << endl;

    }



}













 

















  