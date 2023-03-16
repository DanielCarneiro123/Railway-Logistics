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

    bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue

    int getName() const;

    double getDist() const;
    Edge *getPath() const;
    std::vector<Edge *> getIncoming() const;

    void setId(int info);
    void setVisited(bool visited);
    void setProcesssing(bool processing);
    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    void setPath(Edge *path);
    Edge * addEdge(Vertex *dest, double w);
    bool removeEdge(int destID);

    friend class MutablePriorityQueue<Vertex>;
protected:
    string Name;
    string District;
    string Municipality;
    string Township;
    string Line;
};


#endif //DAV1_STATIONS_H
