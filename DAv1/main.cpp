#include <iostream>
#include "stations.h"
#include "trip.h"


int main() {
    //std::cout << "Hello, World!" << std::endl;
    //stations::readStations();
    trip::readTrips();
    graph g (533, true);
    g.vetorToGraph()
    return 0;
}
