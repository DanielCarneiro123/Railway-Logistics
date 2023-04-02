//
// Created by danie on 22/03/2023.
//

#ifndef DAV2_VERTEXEDGE_H
#define DAV2_VERTEXEDGE_H
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "stations.h"

using namespace std;

class Edge;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

class Vertex {
public:

    Vertex(int id, Stations* station);
    bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue

    int getId() const;
    std::vector<Edge *> getAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    Edge *getPath() const;
    std::vector<Edge *> getIncoming() const;

    void setId(int info);
    void setVisited(bool visited);
    void setProcessing(bool processing);
    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    void setPath(Edge *path);
    bool removeEdge(int destID);
    void readVertex();
    string getName();
    Edge *addEdge(Vertex *d, int w, string service);
protected:
    int id;// identifier
    Stations* stations;


    std::vector<Edge *> adj;  // outgoing edges

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree; // used by topsort
    double dist = 0;
    Edge *path = nullptr;

    std::vector<Edge *> incoming; // incoming edges

    int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS






};

/********************** Edge  ****************************/

class Edge {
public:
    Edge(Vertex* orig, Vertex *dest, int capacity, string service);

    Vertex * getDest() const;
    double getWeight() const;
    bool isSelected() const;
    Vertex * getOrig() const;
    Edge *getReverse() const;
    double getFlow() const;

    void setSelected(bool selected);
    void setReverse(Edge *reverse);
    void setFlow(double flow);
    void readEdges();
protected:
    //Vertex * dest; // destination vertex
    int weight;// edge weight, can also be used for capacity
    //string Source;
    //string Target;
    Vertex* source;
    Vertex* dest;
    string service;



    // auxiliary fields
    bool selected = false;

    // used for bidirectional edges
    Vertex *orig;
    Edge *reverse = nullptr;

    double flow; // for flow-related problems

    Vertex* getSource();

    Vertex* getTarget();

    string getService();
};
#endif //DAV2_VERTEXEDGE_H
