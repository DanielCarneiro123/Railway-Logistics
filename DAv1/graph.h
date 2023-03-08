//
// Created by Daniel on 07/03/2023.
//

#ifndef DAV1_GRAPH_H
#define DAV1_GRAPH_H

#include <list>
#include <vector>
#include "trip.h"
#include "stations.h"

using namespace std;

class graph {
    struct Edge{
        int dest;
        trip cTrips;
    };

    struct Node {
        list<Edge> adj;
        bool visited;
        stations cStations;

    };

    vector<Node> nodes;
};


#endif //DAV1_GRAPH_H
