#include<iostream>
#include "csv.hpp"
#include "coldwarm.hpp"
#include <cstdlib>

using namespace std;
int usage(){
    cout << "====================" << endl;
    cout << "Insufficient arguments" << endl;
    cout << "Use the following:" << endl;
    cout <<  "./main <filepath> <mode>" << endl;
    cout << "Example:" << endl;
    cout << "./main ../datasets/big.csv coldwarm" << endl;
    cout << "====================" << endl;
    return 0;
}
int main(int argc, char* argv[]) {
    if (argc < 3){
        usage();
    }
    else{
        string command = "./cleaner_filter.sh " + string(argv[1]);
        int cleanUp = system(command.c_str());

        if (cleanUp != 0){
            cerr << "Error executing the script:" << command << endl;
            return cleanUp;
        }

        if (string(argv[2]) == "coldwarm")
            return getColdWarm(argc, argv);
    }
}