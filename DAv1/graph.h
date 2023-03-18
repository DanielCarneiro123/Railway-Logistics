//
// Created by Daniel on 07/03/2023.
//

#ifndef DAV1_GRAPH_H
#define DAV1_GRAPH_H

#include <list>
#include <vector>
#include "trip.h"
#include "stations.h"
#include "NodesEdges.h"
#include "set"

using namespace std;

class graph {

    vector<Node> nodes;

    graph(int num, bool dir);
    int n;
    bool hasDir;


    void vetorToGraph(set<trip *>& tripsVec, set<stations *>& stationsVec);
    void bfs(int v);
    void addEdge(int src, int dest, trip trips);
    //void setVisited(Node n, bool visited);
    Node findNode(string nome);

};


#endif //DAV1_GRAPH_H
