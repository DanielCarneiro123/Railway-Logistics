//
// Created by Gonçalo Costa on 08/04/2023.
//

#include "readFiles.h"
#include "Graph.h"
#include <sstream>
#include <fstream>
#include "network.h"
#include "unordered_set"

Graph readFiles::originalGraph(){
    Graph _graph;
    ifstream myFile;
    string currentLine;
    unordered_set<string> set_stations;

    myFile.open("../stations.csv");
    getline(myFile, currentLine);    // ignore first line
    while (getline(myFile, currentLine)) {
        Stations* station = new Stations();
        stringstream iss(currentLine);
        getline(iss, station->Name, ',');
        if (station->Name.front() == '\"') {
            std::string completeName = station->Name;
            while (completeName.back() != '\"' && getline(iss, station->Name, ',')) {
                completeName += "," + station->Name;
            }
            completeName.erase(0, 1);  // remove leading quote
            completeName.erase(completeName.size() - 1);  // remove trailing quote
            station->Name = completeName;
        }

        getline(iss, station->District, ',');
        getline(iss, station->Municipality, ',');
        getline(iss, station->Township, ',');
        if (station->Township.front() == '\"') {
            std::string completeTownship = station->Township;
            while (completeTownship.back() != '\"' && getline(iss, station->Township, ',')) {
                completeTownship += "," + station->Township;
            }
            completeTownship.erase(0, 1);  // remove leading quote
            completeTownship.erase(completeTownship.size() - 1);  // remove trailing quote
            station->Township = completeTownship;
        }
        _graph.addMunicipality(station->Municipality);
        _graph.addDistrict(station->District);
        getline(iss, station->Line, ',');
        if((set_stations.insert(station->Name).second)){
            _graph.addVertex(station);
        }
    }
    myFile.close();

    myFile.open("../network.csv");
    getline(myFile, currentLine);
    set<pair<string,string>> set_network;
    string tempString;
    int inputInt = 1;
    while (getline(myFile, currentLine)) {
        Network *viagem = new Network();
        stringstream inputString(currentLine);
        getline(inputString, viagem->Source, ',');
        if (viagem->Source.front() == '\"') {
            string completeSource = viagem->Source;
            while (completeSource.back() != '\"' && getline(inputString, viagem->Source, ',')) {
                completeSource += "," + viagem->Source;
            }
            completeSource.erase(0, 1);
            completeSource.erase(completeSource.size() - 1);
            viagem->Source = completeSource;
        }
        getline(inputString, viagem->Target, ',');
        if (viagem->Target.front() == '\"') {
            string completeTarget = viagem->Target;
            while (completeTarget.back() != '\"' && getline(inputString, viagem->Target, ',')) {
                completeTarget += "," + viagem->Target;
            }
            completeTarget.erase(0, 1);
            completeTarget.erase(completeTarget.size() - 1);
            viagem->Target = completeTarget;
        }
        _graph.addPair(viagem->Source, viagem->Target);
        getline(inputString, tempString, ',');
        inputInt = stoi(tempString);
        viagem->Capacity = inputInt;
        getline(inputString, viagem->Service, ',');
        if ((set_network.insert(std::make_pair(viagem->Source, viagem->Target)).second)) {
            _graph.addBidirectionalEdge(viagem->Source, viagem->Target, viagem->Capacity, viagem->Service);
        }
    }
    myFile.close();

    return _graph;

}
