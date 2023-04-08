//
// Created by danie on 22/03/2023.
//

#ifndef DAV2_STATIONS_H
#define DAV2_STATIONS_H

#include <string>

using namespace std;

class Stations {
public:

    string Name;
    string District;
    string Municipality;
    string Township;
    string Line;

    string getName();

    string getDistrict();

    string getMunicipality();

    string getTownship();

    string getLine();
};


#endif //DAV2_STATIONS_H
