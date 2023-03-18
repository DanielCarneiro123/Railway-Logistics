//
// Created by Daniel on 07/03/2023.
//

#ifndef DAV1_STATIONS_H
#define DAV1_STATIONS_H

#include <string>

using namespace std;

class stations {
public:

    static void readStations();
    stations();
    stations(string name, string district, string municipality, string township, string line);

    bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue

    string getName() const;
    string getDistrict() const;
    string getMunicipality() const;
    string getTownship() const;
    string getLine() const;

    //friend class MutablePriorityQueue<Vertex>;
protected:
    string Name;
    string District;
    string Municipality;
    string Township;
    string Line;
};


#endif //DAV1_STATIONS_H
