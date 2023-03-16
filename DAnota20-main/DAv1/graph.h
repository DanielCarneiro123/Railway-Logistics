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

struct Edge{
    int dest;
    trip cTrip;
};

struct Node {
    list<Edge> adj;
    bool visited;
    stations cStation;
    int distance;
};


class graph {

    vector<Node> nodes;

    graph(int num, bool dir);
    int n;
    bool hasDir;

    void vetorToGraph(vector<trip>& tripsVec, vector<stations>& stationsVec);
    void bfs(int v);
    void addEdge(int src, int dest, trip trips);
    void setVisited(Node n, bool visited);
    Node findNode(string nome);
};


#endif //DAV1_GRAPH_H
