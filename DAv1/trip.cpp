//
// Created by Daniel on 07/03/2023.
//

#include <fstream>
#include <vector>
#include <sstream>
#include "trip.h"

void readTrips(){
    ifstream myFile;
    string currentLine;
    vector<trip> tripsVec;

    trip viagem;
    myFile.open("../network.csv");
    getline(myFile, currentLine);
    string tempString;
    int tempInt;
    while (getline(myFile, currentLine)){
        stringstream inputString(currentLine);
        getline(inputString, viagem.Source, ',');
        getline(inputString, viagem.Target, ',');
        getline(inputInt, viagem.Capacity, ',');

    }
}
