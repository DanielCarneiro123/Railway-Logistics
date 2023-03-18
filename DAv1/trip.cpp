//
// Created by Daniel on 07/03/2023.
//

#include <fstream>
#include <vector>
#include <sstream>
#include "trip.h"
#include <iostream>
#include <set>

using namespace std;

void trip::readTrips(){
    ifstream myFile;
    string currentLine;
    set<trip *> tripsSet;

    trip viagem;
    myFile.open("../network.csv");
    getline(myFile, currentLine);
    string tempString;
    int inputInt;
    while (getline(myFile, currentLine)){
        stringstream inputString(currentLine);
        getline(inputString, viagem.Source, ',');
        getline(inputString, viagem.Target, ',');
        getline(inputString, tempString, ',');
        inputInt = stoi(tempString);
        viagem.Capacity = inputInt;
        getline(inputString, viagem.Service, ',');
        tripsSet.insert(&viagem);
    }

    for(auto elem : tripsSet){
        cout << elem->Service << endl;
        cout << elem->Capacity << endl;
        cout << elem->Source << endl;
        cout << elem->Target << endl;
        cout << endl;

    }
    cout << tripsSet.size() << endl;

    myFile.close();

}
trip::trip() {}

trip::trip(std::string service, int capacity, std::string source, std::string target) {
    this->Capacity = capacity;
    this->Target = target;
    this->Source = source;
    this->Service = service;
}

string trip::getSource() const {
    return this->Source;
}

string trip::getTarget() const {
    return this->Target;
}

int trip::getCapacity() const {
    return this->Capacity;
}

string trip::getService() const {
    return this->Service;
}