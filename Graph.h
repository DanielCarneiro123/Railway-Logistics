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
#include <map>
#include <set>



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
    bool addVertex(Stations* station);
    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addBidirectionalEdge(const int &source, const int &dest, double w);

    int getNumVertex() const;
    int getNumEdge() const;
    std::vector<Vertex *> getVertexSet() const;


    Vertex *findSource(const string &source) const;

    Vertex *findSourceTarget(const string &source) const;

    bool addEdge(const string &sourc, const string &dest, int w, string service);

    bool removeEdge(const int &source, const int &dest);

    bool findAugmentingPath(Vertex *src, Vertex *dest);

    double findMinResidualAlongPath(Vertex *src, Vertex *dest);

    void augmentFlowAlongPath(Vertex *src, Vertex *dest, double f);

    Graph createSubgraph ();
    vector<Vertex*> kthAfectedNodes(int k);

    void testAndVisit(queue<Vertex *> &queue, Edge *e, Vertex *w, double residual);

    int maxFlow(int idA, int idB);

    int edmondsKarp(int source, int target);

    void addPair(string key, string value);
    void max();
    void addMunicipality(string municipio);
    void addDistrict(string distrito);


    set<Vertex *> getVerticesByMunicipality(const string &municipality, Graph &g);
    set<Vertex*> getVerticesByDistrict(const string &distrito, Graph &g);
        void createSuperSink(const string &name, Graph &g, bool is_mun);
    set<Vertex*> getVerticesNotInMunicipality(const string &municipality, Graph &g);
    set<Vertex*> getVerticesNotInDistrict(const string &distrito, Graph &g);
    void createSuperSource(const string &name, Graph &g, bool is_mun);
    //static bool cmp(pair<string, int>& a, pair<string, int>& b);
    static bool cmp(const pair<string, int>& a, const pair<string, int>& b);
    void sort(unordered_map<string, int>& maxFlowsMuni,int k);
    void percorrerMunicipios(int k, bool is_mun);
    Graph copy() const;



    bool addBidirectionalEdge(const string &sourc, const string &dest, int w, string service);
    int minVertexAdjSize(Graph &g);
    Vertex* getVertex(string name);
    void createSuperSourceV2(const int idA);
    double arrivingTrains(int sink);
    void Dijkstra(int idA);
    double operationCost(int idA, int idB);

    void menu2_1(string A, string B);
    void menu2_4(string A);


protected:

    std::vector<Vertex*> vertexSet;    // vertex set
    std::unordered_map<string , Vertex*> vertexMap;
    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall

    /*
     * Finds the index of the vertex with a given content.
     */
    int findVertexIdx(const int &id) const;


    vector<pair<string, string>> pairs;

    set<string> municipios;

    set<string> distritos;

    int maxFlowMunici(int idA, int idB);

    void removeVertex(int id);

};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);

#endif //DAV2_GRAPH_H
