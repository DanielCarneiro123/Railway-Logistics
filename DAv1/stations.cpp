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

void stations::readStations() {
    ifstream myFile;
    string currentLine;
    set<stations*> stationsSet;
    stations station;

    std::set<string> lines;
    myFile.open("/Users/goncalocosta/Desktop/2ano/2semestre/DAprojeto/Project1Data/stations.csv");
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
        //lines.insert(station.Line);
        stationsSet.insert(&station);
    }

    for(auto elem:stationsSet){
        cout << elem->Name << endl;
        cout << elem->Township << endl;
        cout << elem->Line << endl;
        cout << elem->District << endl;
        cout << elem->Municipality << endl;
        cout << endl;

    }
    cout << stationsSet.size() << endl;

    myFile.close();
}

stations::stations() {}

stations::stations(std::string name, std::string district, std::string municipality, std::string township,
                   std::string line) {
    this->Name = name;
    this->Township = township;
    this->Line = line;
    this->Municipality = municipality;
    this->District = district;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
/*
Edge * Vertex::addEdge(Vertex *d, double w) {
    auto newEdge = new Edge(this, d, w);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}
*/
/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
/*
bool stations::removeEdge(int destID) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Vertex *dest = edge->getDest();
        if (dest->getId() == destID) {
            it = adj.erase(it);
            // Also remove the corresponding edge from the incoming list
            auto it2 = dest->incoming.begin();
            while (it2 != dest->incoming.end()) {
                if ((*it2)->getOrig()->getId() == id) {
                    it2 = dest->incoming.erase(it2);
                }
                else {
                    it2++;
                }
            }
            delete edge;
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
    }
    return removedEdge;
} */



string stations::getName() const {
    return this->Name;
}

string stations::getDistrict() const {
    return this->District;
}
string stations::getMunicipality() const {
    return this->Municipality;
}
string stations::getTownship() const {
    return this->Township;
}
string stations::getLine() const {
    return this->Line;
}


