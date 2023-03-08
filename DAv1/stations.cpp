//
// Created by Daniel on 07/03/2023.
//

#include "stations.h"
#include <string>
#include <vector>
#include <fstream>
#include <vector>
#include <sstream>
#include <set>
#include <iostream>

void readStations() {
    ifstream myFile;
    string currentLine;
    vector<stations> stationsVec;

    stations station;

    std::set<string> lines;
    myFile.open("../network.csv");
    getline(myFile, currentLine);    // ignore first line
    while (getline(myFile, currentLine)) {
        istringstream iss(currentLine);
        string name, district, municipality, township, linename;

        getline(iss, station.Name, ',');
        if (station.Name.front() == '\"') {
            std::string completeName = station.Name;
            while (completeName.back() != '\"' && getline(iss, station.Name, ',')) {
                completeName += "," + station.Name;
            }
            completeName.erase(0, 1);  // remove leading quote
            completeName.erase(completeName.size() - 1);  // remove trailing quote
            station.Name = completeName;
        }
        getline(iss, station.District, ',');
        getline(iss, station.Municipality, ',');
        getline(iss, station.Township, ',');
        if (township.front() == '\"') {
            std::string completeTownship = station.Township;
            while (completeTownship.back() != '\"' && getline(iss, station.Township, ',')) {
                completeTownship += "," + station.Township;
            }
            completeTownship.erase(0, 1);  // remove leading quote
            completeTownship.erase(completeTownship.size() - 1);  // remove trailing quote
            station.Township = completeTownship;
        }
        getline(iss, station.Line, ',');
        lines.insert(station.Line);

    }

    for(auto elem:lines){
        cout << elem << endl;
    }

}