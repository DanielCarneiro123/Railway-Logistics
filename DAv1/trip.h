//
// Created by Daniel on 07/03/2023.
//

#ifndef DAV1_TRIP_H
#define DAV1_TRIP_H

#include <string>

using namespace std;

class trip {
public:
    trip();
    trip(string service, int capacity, string source, string target);
    static void readTrips();

    int getCapacity() const; //capacity
    string getSource() const;
    string getTarget() const;
    string getService() const;

protected:

    string Source;
    string Target;
    int Capacity;
    string Service;

/*não sei se isto daqui para baixo é aqui
    Vertex * dest; // destination vertex
    double weight; // edge weight, can also be used for capacity

    // auxiliary fields
    bool selected = false;

    // used for bidirectional edges
    Vertex *orig;
    Edge *reverse = nullptr;

    double flow; // for flow-related problems
    */
};


#endif //DAV1_TRIP_H
