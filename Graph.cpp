//
// Created by danie on 22/03/2023.
//
#include <fstream>
#include <sstream>
#include "Graph.h"
#include "VertexEdge.h"

int Graph::getNumVertex() const {
    return vertexSet.size();
}

std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
Vertex * Graph::findVertex(const int &id) const {
    for (auto v : vertexSet)
        if (v->getId() == id)
            return v;
    return nullptr;
}

Vertex * Graph::findSourceTarget(const string &name) const {
    for (auto v : vertexSet)
        if (v->getName() == name)
            return v;
    return nullptr;
}


/*
 * Finds the index of the vertex with a given content.
 */
int Graph::findVertexIdx(const int &id) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getId() == id)
            return i;
    return -1;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
bool Graph::addVertex(Stations station) {
    Vertex*  new_vertex = new Vertex(vertexSet.size(), &station);
    vertexSet.push_back(new_vertex);
    vertexMap.insert({station.Name, new_vertex});
    return true;
}
/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
bool Graph::addEdge(const string &sourc, const string &dest, int w, string service) {
    auto v1 = vertexMap[sourc];
    auto v2 = vertexMap[dest];
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w, service);
    return true;
}

bool Graph::addBidirectionalEdge(const string &sourc, const string &dest, int w, string service) {
    auto v1 = vertexMap[sourc];
    auto v2 = vertexMap[dest];
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w/2, service);
    auto e2 = v2->addEdge(v1, w/2, service);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}



Graph::~Graph() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}


void Graph::testAndVisit(std::queue<Vertex*>& queue, Edge* e, Vertex* w, double residual){
    if (!w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        queue.push(w);
    }
}


bool Graph::findAugmentingPath(Vertex* src, Vertex* dest){
    for (Vertex*  v : vertexSet)
        v->setVisited(false);

    src->setVisited(true);

    std::queue<Vertex*> queue;
    queue.push(src);

    while (!queue.empty() && !dest->isVisited()){
        Vertex* v = queue.front();
        queue.pop();

        for (Edge* e: v->getAdj())
            testAndVisit(queue,e,e->getDest(),e->getWeight()-e->getFlow());

        for (Edge* e: v->getIncoming())
            testAndVisit(queue,e,e->getOrig(),e->getFlow());
    }

    return dest->isVisited();
}

double Graph::findMinResidualAlongPath(Vertex* src, Vertex* dest){
    double f = INF;
    for(Vertex* v = dest; v != src;){
        Edge* e = v->getPath();
        if (e->getDest() == v){
            f = std::min(f,e->getWeight()-e->getFlow());
            v = e->getOrig();
        }
        else{
            f = std::min(f,e->getFlow());
            v = e->getDest();
        }
    }
    return f;
}

void Graph::augmentFlowAlongPath(Vertex *src, Vertex *dest, double f){
    for (Vertex* v = dest; v != src;){
        Edge* e = v->getPath();
        double flow = e->getFlow();

        //capacidade residual
        if (e->getDest() == v){
            e->setFlow(flow+f);
            v = e->getOrig();
        }

            //fluxo no sentido oposto
        else{
            e->setFlow(flow-f);
            v = e->getDest();
        }
    }
}


void Graph::edmondsKarp(int source, int target) {
    Vertex* src = findVertex(source);
    Vertex*  dest = findVertex(target);
    if (src == nullptr || dest == nullptr || src == dest)
        return;

    //reset dos fluxos
    for (Vertex*  v : vertexSet)
        for (Edge* e : v->getAdj())
            e->setFlow(0);

    //encontrar caminhos de aumento de fluxo
    while (findAugmentingPath(src,dest)) {
        auto f = findMinResidualAlongPath(src, dest);
        augmentFlowAlongPath(src, dest, f);
    }

    for(Edge* e: src->getAdj()){
        cout << e->getFlow() << endl;
    }

}

void Graph::teste(int idA, int idB){
    edmondsKarp(idA,idB);
}
