#include <iostream>
#include "coldwarm.hpp"
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
    TApplication app("app", nullptr, nullptr);

    string mode;
    string filepath;

    cout << "Enter the filepath: ";
    getline(cin, filepath);

    

    if (!isValidFilePath(filepath)) {
        cout << "Invalid filepath!" << endl;
        return 1;
    }

    while (true) {
        cout << "-----------------------" << endl;
        cout << "Choose a mode or type 'exit' to quit. " << endl;
        cout << " " << endl;
        cout << "Modes: coldwarm, 4dates, winter" << endl;
        cout << "-----------------------" << endl;
        getline(cin, mode);

        if (mode == "exit") {
            cout << "-----------------------" << endl;
            cout << "Exiting program..." << endl;
            break;
        }

        if (!isValidMode(mode)) {
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

        if (mode == "coldwarm") {
            getColdWarm(filepath);
            cout << "Graph generated. Press Enter to exit..." << endl;
            cin.get();
            app.Terminate(); // Wait for user input to ensure they see the graph
            break; // Exit the loop after processing
        }
    }

    return 0; // Return success
}
