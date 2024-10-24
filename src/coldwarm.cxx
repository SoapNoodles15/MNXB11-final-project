#include "csv.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <filesystem>

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
                    coldTempsMap[year] = temperature; // Update coldest temperature
                }

                if (warmTempsMap.find(year) == warmTempsMap.end() || temperature > warmTempsMap[year]) { 
                    warmTempsMap[year] = temperature; // Update warmest temperature
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

// A function to actually obtain the data
int getColdWarm(string filePath) {
    string filePathName = std::filesystem::path(filePath).filename().string();
    string filename = "ColdestWarmest_filtered_" + filePathName;

    vector<int> years;
    vector<double> coldestTemps;
    vector<double> warmestTemps;

    parseCSV(filename, years, coldestTemps, warmestTemps);

    // Printing out the years and temperatures
    cout << "Years and Temperatures:" << endl;
    for (size_t i = 0; i < years.size(); i++) {
        cout << "Year: " << years[i] << ", Coldest Temp: " << coldestTemps[i] << ", Warmest Temp: " << warmestTemps[i] << endl;
    }

    return 0;
}
