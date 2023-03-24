#include <iostream>
#include "Graph.h"
#include "network.h"
#include <sstream>
#include <fstream>

void createEdges(Graph &g){
    ifstream myFile;
    string currentLine;
    Network viagem;
    myFile.open("../network.csv");
    getline(myFile, currentLine);
    string tempString;
    int inputInt = 1;
    while (getline(myFile, currentLine)){
        stringstream inputString(currentLine);
        getline(inputString, viagem.Source, ',');
        if (viagem.Source.front() == '\"') {
            string completeSource = viagem.Source;
            while (completeSource.back() != '\"' && getline(inputString, viagem.Source, ',')) {
                completeSource += "," + viagem.Source;
            }
            completeSource.erase(0, 1);
            completeSource.erase(completeSource.size() - 1);
            viagem.Source = completeSource;
        }
        getline(inputString, viagem.Target, ',');
        if (viagem.Target.front() == '\"') {
            string completeTarget = viagem.Target;
            while (completeTarget.back() != '\"' && getline(inputString, viagem.Target, ',')) {
                completeTarget += "," + viagem.Target;
            }
            completeTarget.erase(0, 1);
            completeTarget.erase(completeTarget.size() - 1);
            viagem.Target = completeTarget;
        }
        getline(inputString, tempString, ',');
        inputInt = stoi(tempString);
        viagem.Capacity = inputInt;
        getline(inputString, viagem.Service, ',');
        g.addEdge(viagem.Source, viagem.Target, viagem.Capacity, viagem.Service);
    }
    myFile.close();
}

void createVertexes(Graph &g){
    ifstream myFile;
    string currentLine;
    Stations station;
    myFile.open("../stations.csv");
    getline(myFile, currentLine);    // ignore first line
    while (getline(myFile, currentLine)) {
        istringstream iss(currentLine);
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
        if (station.Township.front() == '\"') {
            std::string completeTownship = station.Township;
            while (completeTownship.back() != '\"' && getline(iss, station.Township, ',')) {
                completeTownship += "," + station.Township;
            }
            completeTownship.erase(0, 1);  // remove leading quote
            completeTownship.erase(completeTownship.size() - 1);  // remove trailing quote
            station.Township = completeTownship;
        }
        getline(iss, station.Line, ',');
        g.addVertex(station);
    }
    myFile.close();

}


int main() {
    Graph g;
    createVertexes(g);
    createEdges(g);
    g.edmondsKarp(483,321);
    
    std::cout << g.getVertexSet().size() << std::endl;
    return 0;
}
