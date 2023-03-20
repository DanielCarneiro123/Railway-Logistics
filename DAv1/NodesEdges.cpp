//
// Created by Gonçalo Costa on 18/03/2023.
//

#include "NodesEdges.h"

stations Node::getStation() const{
    return this->cStation;
}

void Node::setStation(stations s) {
    this->cStation = s;
}

trip Edge::getTrip() const {
    return this->cTrip;
}

void Node::setVisited(bool visited) {
    this->visited = visited;
}

void Node::setProcesssing(bool processing) {
    this->processing = processing;
}
void Node::setIndegree(unsigned int indegree) {
    this->indegree = indegree;
}
void Node::setDist(int dist) {
    this->dist = dist;
}

void Node::setPath(Edge *path) {
    this->path = path;
}

list<Edge> Node::getAdj() const {
    return this->adj;
}
/*
Edge * Node::addEdge(Node *d, double w) {
    auto newEdge = new Edge(this, d, w);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}
 */
/*
bool Node::removeEdge(string destName) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Node *dest = edge->getDest();
        if (dest->getStation().getName() == destName) {
            it = adj.erase(it);
            // Also remove the corresponding edge from the incoming list
            auto it2 = dest->incoming.begin();
            while (it2 != dest->incoming.end()) {
                if ((*it2)->getOrig()->getId() == id) {
                    it2 = dest->incoming.erase(it2);
                }
                else {
                    it2++;
                }
            }
            delete edge;
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
    }
    return removedEdge;
}
 */

// Edge

//Edge::Edge(Node *orig, Node *dest, double w): *, dest(dest), weight(w) {} // ???????????????

Node * Edge::getDest() const {
    return dest;
}
bool Edge::isSelected() const {
    return this->selected;
}
Node * Edge::getOrig() const {
    return this->orig;
}
Edge *Edge::getReverse() const {
    return this->reverse;
}
double Edge::getFlow() const {
    return flow;
}
void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}
void Edge::setSelected(bool selected) {
    this->selected = selected;
}

Edge::Edge() {}

void Edge::setTrip(trip t) {
    this->cTrip = t;
}
