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
    set<trip *> tripsVec;

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
        tripsVec.insert(&viagem);
    }

    for(auto elem : tripsVec){
        cout << elem->Service << endl;
        cout << elem->Capacity << endl;
        cout << elem->Source << endl;
        cout << elem->Target << endl;
        cout << endl;

    }
    cout << tripsVec.size() << endl;

    myFile.close();

}
trip::Edge(stations *orig, stations *dest, double w): orig(orig), dest(dest), weight(w) {}

stations * trip::getDest() const {
    return this->dest;
}

double trip::getWeight() const {
    return this->weight;
}

trip * trip::getOrig() const {
    return this->orig;
}

trip *trip::getReverse() const {
    return this->reverse;
}

bool trip::isSelected() const {
    return this->selected;
}

double trip::getFlow() const {
    return flow;
}

void trip::setSelected(bool selected) {
    this->selected = selected;
}

void trip::setReverse(trip *reverse) {
    this->reverse = reverse;
}

void trip::setFlow(double flow) {
    this->flow = flow;
}