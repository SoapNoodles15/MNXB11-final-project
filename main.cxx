#include <iostream>
#include "coldwarm.hpp"
#include "destinctdates.h"
#include "winter3.h"
#include <cstdlib>
#include <filesystem>
#include <TApplication.h>


using namespace std;
namespace fs = std::filesystem;

// Function to check if the mode is valid
bool isValidMode(const string& mode) {
    return mode == "coldwarm" || mode == "4dates" || mode == "winter";
}

// Function to check if the filepath is valid
bool isValidFilePath(const string& filepath) {
    return fs::exists(filepath) && fs::is_regular_file(filepath); // Checking if file exists and is a regular file
}

int main() {
    TApplication app("app", nullptr, nullptr); // Initializing the ROOT application
    string mode; // Initializing the mode and filepath strings
    string filepath;

    cout << "Enter the filepath: ";
    getline(cin, filepath); // Obtaining the filepath from user input

    

    if (!isValidFilePath(filepath)) { // Checking if the filepath is valid
        cout << "Invalid filepath!" << endl;
        return 1;
    }

    while (true) {
        cout << "-----------------------" << endl;
        cout << "Choose a mode or type 'exit' to quit. " << endl;
        cout << " " << endl;
        cout << "Modes: coldwarm, 4dates, winter" << endl;
        cout << "-----------------------" << endl;
        getline(cin, mode); // Getting the mode from user input

        if (mode == "exit") { // If user decides to exit
            cout << "-----------------------" << endl;
            cout << "Exiting program..." << endl;
            break;
        }

        if (!isValidMode(mode)) { // Checking if mode is valid
            cerr << "Invalid mode selected!" << endl;
            continue;
        }

        // Pre-processing script is run here
        string command = "./cleaner_filter.sh " + filepath;
        int cleanUp = system(command.c_str());

        // Checking if it ran correctly
        if (cleanUp != 0) {
            cerr << "Error executing the script: " << command << endl;
            return cleanUp;
        }

        if (mode == "coldwarm") { // If statements executing functions depending on what mode the user chose
            getColdWarm(filepath);
            cout << "Press Enter to close the application..." << endl;
            cin.get();
            app.Terminate();
            break;
        }
        if (mode == "4dates"){
            getFourDates(filepath);
            cout << "Press Enter to close the application..." << endl;
            cin.get();
            app.Terminate();
            break;
        }
        if (mode == "winter"){
            getWinter(filepath);
            cout << "Press Enter to close the application..." << endl;
            cin.get();
            app.Terminate();
            break;
        }      
    }

    return 0; // Return success
}
