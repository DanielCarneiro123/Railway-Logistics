//
// Created by danie on 22/03/2023.
//

#include <sstream>
#include <fstream>
#include "VertexEdge.h"
#include "Graph.h"
#include "network.h"
#include "stations.h"

/************************* Vertex  **************************/

Vertex::Vertex(int id, Stations* station): id(id){
    this->stations = station;
}



/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */


Edge * Vertex::addEdge(Vertex *d, int w, string service) {
    auto newEdge = new Edge(this, d, w,service);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
/*
bool Vertex::removeEdge(int destID) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Vertex *dest = edge->getDest();
        if (dest->getId() == destID) {
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
}*/

bool Vertex::operator<(Vertex & vertex) const {
    return this->dist < vertex.dist;
}

int Vertex::getId() const {
    return this->id;
}

string Vertex::getMunicipality() const {
    return this->stations->Municipality;
}



std::vector<Edge*> Vertex::getAdj() const {
    return this->adj;
}

bool Vertex::isVisited() const {
    return this->visited;
}

bool Vertex::isProcessing() const {
    return this->processing;
}

unsigned int Vertex::getIndegree() const {
    return this->indegree;
}

double Vertex::getDist() const {
    return this->dist;
}

Edge *Vertex::getPath() const {
    return this->path;
}

std::vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}

void Vertex::setId(int id) {
    this->id = id;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

void Vertex::setProcessing(bool processing) {
    this->processing = processing;
}

void Vertex::setIndegree(unsigned int indegree) {
    this->indegree = indegree;
}

void Vertex::setDist(double dist) {
    this->dist = dist;
}

void Vertex::setPath(Edge *path) {
    this->path = path;
}

string Vertex::getName(){
    return this->stations->Name;
}

Stations *Vertex::getStation() {
    return this->stations;
}

void Vertex::setStation(Stations *Stations) {
    this->stations = Stations;
}
/*
void Vertex::readVertex() {
    ifstream myFile;
    string currentLine;
    Stations station;
    myFile.open("../stations.csv");
    getline(myFile, currentLine);    // ignore first line
    while (getline(myFile, currentLine)) {
        istringstream iss(currentLine);
        getline(iss, station.Name, ',');
        if (station.Name.front() == '\"') {
            std::string completeName = station.Name;
            while (completeName.back() != '\"' && getline(iss, station.Name, ',')) {
                completeName += "," + station.Name;
            }
            completeName.erase(0, 1);  // remove leading quote
            completeName.erase(completeName.size() - 1);  // remove trailing quote
            station.Name = completeName;
        }
        getline(iss, station.District, ',');
        getline(iss, station.Municipality, ',');
        getline(iss, station.Township, ',');
        if (station.Township.front() == '\"') {
            std::string completeTownship = station.Township;
            while (completeTownship.back() != '\"' && getline(iss, station.Township, ',')) {
                completeTownship += "," + station.Township;
            }
            completeTownship.erase(0, 1);  // remove leading quote
            completeTownship.erase(completeTownship.size() - 1);  // remove trailing quote
            station.Township = completeTownship;
        }
        getline(iss, station.Line, ',');
        g.addVertex(station);
    }
    myFile.close();

}*/



/********************** Edge  ****************************/

Edge::Edge(Vertex *orig, Vertex *dest, int capacity, string service): orig(orig), dest(dest), weight(capacity), service(service) {}

Vertex * Edge::getDest() const {
    return this->dest;
}
double Edge::getWeight() const {
    return this->weight;
}

Vertex * Edge::getOrig() const {
    return this->orig;
}

Edge *Edge::getReverse() const {
    return this->reverse;
}

bool Edge::isSelected() const {
    return this->selected;
}

double Edge::getFlow() const {
    return flow;
}

void Edge::setSelected(bool selected) {
    this->selected = selected;
}

void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}

void Edge::setFlow(double flow) {
    this->flow = flow;
}

Vertex* Edge::getSource(){
    return this->source;
}

Vertex* Edge::getTarget(){
    return this->dest;
}


string Edge::getService(){
    return this->service;
}
/*
void Edge::readEdges(){
    ifstream myFile;
    string currentLine;
    int i = 0;
    Network viagem;
    myFile.open("../network.csv");
    getline(myFile, currentLine);
    string tempString;
    int inputInt = 1;
    while (getline(myFile, currentLine)){
        stringstream inputString(currentLine);
        getline(inputString, viagem.Source, ',');
        getline(inputString, viagem.Target, ',');
        getline(inputString, tempString, ',');
        inputInt = stoi(tempString);
        viagem.Capacity = inputInt;
        getline(inputString, viagem.Service, ',');
        g.addEdge(viagem.Source, viagem.Target, viagem.Capacity, viagem.Service);
    }
    myFile.close();

}*/