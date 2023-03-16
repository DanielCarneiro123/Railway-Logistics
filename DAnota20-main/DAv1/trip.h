//
// Created by Daniel on 07/03/2023.
//

#ifndef DAV1_TRIP_H
#define DAV1_TRIP_H

#include <string>

using namespace std;

class trip {
public:
    string Source;
    string Target;
    int Capacity;
    string Service;

    static void readTrips();
    Edge(Vertex *orig, Vertex *dest, double w);

    Vertex * getDest() const;
    double getWeight() const;
    bool isSelected() const;
    Vertex * getOrig() const;
    Edge *getReverse() const;
    double getFlow() const;

    void setSelected(bool selected);
    void setReverse(Edge *reverse);
    void setFlow(double flow);
protected:
    Vertex * dest; // destination vertex
    double weight; // edge weight, can also be used for capacity

    // auxiliary fields
    bool selected = false;

    // used for bidirectional edges
    Vertex *orig;
    Edge *reverse = nullptr;

    double flow; // for flow-related problems
};


#endif //DAV1_TRIP_H
