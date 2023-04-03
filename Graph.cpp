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
bool Graph::addVertex(Stations *station) {
    Vertex* new_vertex = new Vertex(vertexSet.size(), station);
    vertexSet.push_back(new_vertex);
    vertexMap.insert({station->Name, new_vertex});
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

void Graph::addPair(string key, string value){
    pairs.insert(make_pair(key,value));
}

void Graph::addMunicipality(string municipio){
    municipios.insert(municipio);
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
}

int Graph::maxFlow(int idA, int idB){

    int max = 0;

    Vertex* src = findVertex(idA);
    Vertex*  dest = findVertex(idB);

    edmondsKarp(idA,idB);

    for(auto elem : dest->getIncoming()){
        max += elem->getFlow();
    }

    cout << "O maximo flow entre " << src->getName() << " e " << dest->getName() << " é " << max << endl;  // depois tirar esta linha e colocar no menu

    return max;

}

int Graph::maxFlowMunici(int idA, int idB){

    int max = 0;

    Vertex* src = findVertex(idA);
    Vertex*  dest = findVertex(idB);

    edmondsKarp(idA,idB);

    for(auto edge : dest->getIncoming()){
        for(auto elem : edge->getOrig()->getIncoming())
            max += edge->getFlow();
    }

    cout << "O maximo flow entre " << src->getName() << " e " << dest->getName() << " é " << max << endl;  // depois tirar esta linha e colocar no menu

    return max;

}

void Graph::max(){

    int maxAtual = -1, idA, idB;
    int flowMaximo;
    map<string, string> maxPair;

    for(auto pair : pairs){
        cout << pair.first << " " << pair.second << endl;
    }

    for (auto pair : pairs){

        for(auto vertex : vertexSet){
            if(vertex->getName() == pair.first){
                idA = vertex->getId();
            }
            if(vertex->getName() == pair.second){
                idB = vertex->getId();
            }
        }

        flowMaximo = maxFlow(idA,idB);

        if(flowMaximo > maxAtual){
            maxPair.clear();
            maxAtual = flowMaximo;
            maxPair[pair.first] = pair.second;
        }
        if(flowMaximo == maxAtual){
            maxPair[pair.first] = pair.second;
        }

    }

    cout << "A(s) viagens que exigem mais comboios:" << endl;
    for(auto pair : maxPair){
        cout << pair.first << " com destino a " << pair.second << endl;
    }
}

vector<Vertex*> Graph::getVerticesByMunicipality(const string &municipality) {
    vector<Vertex*> result;
    for (auto vertex : vertexSet) {
        if (vertex->getStation()->Municipality == municipality) {
            result.push_back(vertex);
        }
    }
    return result;
}

void Graph::createSuperSink(const string &municipality) {
    Stations* station = new Stations();

    station->Name = "supersink";
    addVertex(station);
    for (auto vertex : getVerticesByMunicipality(municipality)) {
        addEdge(vertex->getName(),station->Name, INT_MAX, "");
    }

}

vector<Vertex*> Graph::getVerticesNotInMunicipality(const string &municipality) {
    vector<Vertex*> result;
    for (auto vertex : vertexSet) {
        if (vertex->getStation()->Municipality != municipality && vertex->getStation()->Municipality != "resto" && vertex->getStation()->Name != "supersink") {
            result.push_back(vertex);
        }
    }
    return result;
}

void Graph::createSuperSource(const string &municipality) {
    Stations* station = new Stations();
    station->Name = "supersource";
    station->Municipality = "resto";
    //supersource->setId(99999);
    addVertex(station);
    for (auto vertex : getVerticesNotInMunicipality(municipality)) {
        addEdge(station->Name, vertex->getStation()->Name, INT_MAX, "");
    }
}

bool Graph::cmp(pair<string, int>& a, pair<string, int>& b){
    return a.second < b.second;
}


void Graph::sort(map<string, int>& maxFlowsMuni){

    vector<pair<string, int> > A;

    for (auto& it : maxFlowsMuni) {
        A.push_back(it);
    }

    std::sort(A.begin(), A.end(), cmp);

    for (auto& it : A) {
        maxFlowsMuni.insert(std::make_pair(it.first, it.second));
    }
}

void Graph::percorrerMunicipios(){

    map<string,int> maxFlowsMuni;
    int idA;

    for(auto municipio : municipios){

        for(auto vertex : vertexSet){  //fazer uma função que retorne o id
            if(vertex->getMunicipality() == municipio){
                idA = vertex->getId();
            }
        }

        createSuperSink(municipio);
        createSuperSource(municipio);
        int flow = maxFlowMunici(vertexSet.size()-1,vertexSet.size()-2);
        maxFlowsMuni[municipio] = flow;
    }

    sort(maxFlowsMuni);

    for (auto elem : maxFlowsMuni){
        cout << elem.first << " = " << elem.second << endl;
    }

}
