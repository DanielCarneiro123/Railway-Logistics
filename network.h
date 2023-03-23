//
// Created by danie on 22/03/2023.
//

#ifndef DAV2_NETWORK_H
#define DAV2_NETWORK_H

#include <string>

using namespace std;

class Network {
public:
    string Source;
    string Target;
    int Capacity;
    string Service;

    string getSource();

    string getTarget();

    int getCapacity();

    string getService();
};


#endif //DAV2_NETWORK_H
