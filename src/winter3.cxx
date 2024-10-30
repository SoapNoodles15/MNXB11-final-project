#include "winter3.h"
#include "csv.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <filesystem>

using std::string;
using std::vector;
namespace fs = std::filesystem;

int extractYear(const string& date) {
    return stoi(date.substr(0, 4));
}
// Constructor implementation
winter::winter(const std::string& Winter_filtered_Falun)
    : filename(Winter_filtered_Falun) {}

// Process temperature data from the CSV
void winter::getWinter() {
    csv::CSVReader csv(filename);

    std::map<int, std::vector> winter_map;

    // Iterate over each row of the CSV file
    for (const auto& row : csv) {
        std::string date_str = row[0];   // Get date (YYYY-MM-DD)
        std::double temp_str = row[2];   // Get temperature

        int year = extractYear(date_str); // Extract just the year

        year_to_temperatures[year].push_back(temperature);  // Add temperature to the map entry for that year
    }
}


void winter::calculateYearlyAverages() {
    for (const auto& entry : year_to_temperatures) {
        int year = entry.first;
        const std::vector<double>& temps = entry.second;

        // Calculate the average temperature for the year
        double sum = 0;
        for (double temp : temps) {
            sum += temp;
        }
        double average_temp = sum / temps.size();  // Calculate the average
        yearly_avg_temperatures[year] = average_temp;  // Store the average temperature
    }
}