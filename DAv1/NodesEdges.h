//
// Created by Gonçalo Costa on 18/03/2023.
//

#ifndef DAV1_NODESEDGES_H
#define DAV1_NODESEDGES_H

#include "trip.h"
#include "stations.h"
#include <list>

class Edge;

class Node {
public:

    stations getStation() const;
    void setStation(stations s);
    list<Edge> getAdj() const;

    /* RELACIONADO COM OS NODES*/
    double getDist() const;
    Edge *getPath() const;
    std::vector<Edge *> getIncoming() const;

    //void setId(int info);
    void setVisited(bool visited);
    void setProcesssing(bool processing);
    void setIndegree(unsigned int indegree);
    void setDist(int dist);
    void setPath(Edge *path);
    //Edge * addEdge(Node *dest, double w);
    //bool removeEdge(string destName);


protected:
    list<Edge> adj;
    bool visited;
    stations cStation;
    int distance;
    Edge *path = nullptr;
    bool processing = false; // NÂO SEI SE VAMOS PRECISAR MAS used by isDAG (in addition to the visited attribute)
    unsigned int indegree; // NÂO SEI SE VAMOS PRECISAR MAS used by topsort
    int dist = 0;


    std::vector<Edge *> incoming; // incoming edges

};

class Edge {
public:

    trip getTrip() const;

    //Edge(Node *orig, Node *dest, double w);

    Node * getDest() const;
    bool isSelected() const;
    Node * getOrig() const;
    Edge *getReverse() const;
    double getFlow() const;
    void setSelected(bool selected);
    void setReverse(Edge *reverse);
    void setFlow(double flow);


protected:
    int dest; //ou então meter string dest com o nome do node
    trip cTrip;

    bool selected = false;

    // used for bidirectional edges
    Node *orig;
    Edge *reverse = nullptr;

    double flow; // for flow-related problems

};


#endif //DAV1_NODESEDGES_H
