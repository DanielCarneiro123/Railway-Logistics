//
// Created by danie on 22/03/2023.
//

#ifndef DAV2_GRAPH_H
#define DAV2_GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <unordered_map>


#include "VertexEdge.h"

class Graph {
public:
    ~Graph();
    /*
    * Auxiliary function to find a vertex with a given ID.
    */
    Vertex *findVertex(const int &id) const;
    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    //void addVertex(Vertex &v);
    bool addVertex(Stations station);
    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addBidirectionalEdge(const int &source, const int &dest, double w);

    int getNumVertex() const;
    std::vector<Vertex *> getVertexSet() const;


    Vertex *findSource(const string &source) const;

    Vertex *findSourceTarget(const string &source) const;

    bool addEdge(const string &sourc, const string &dest, int w, string service);

protected:

    std::vector<Vertex*> vertexSet;    // vertex set
    std::unordered_map<string , Vertex*> vertexMap;
    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall

    /*
     * Finds the index of the vertex with a given content.
     */
    int findVertexIdx(const int &id) const;


    bool addBidirectionalEdge(const string &sourc, const string &dest, int w, string service);
};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);

#endif //DAV2_GRAPH_H
