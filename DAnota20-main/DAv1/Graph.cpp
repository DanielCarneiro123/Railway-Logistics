//
// Created by danie on 22/03/2023.
//
#include <fstream>
#include <sstream>
#include "Graph.h"
#include "VertexEdge.h"
#include "unordered_set"
#include "MutablePrioityQueue.h"
#include "readFiles.h"

std::vector<Vertex*> alteredSources;
std::vector<Vertex*> alteredTargets;
std::vector<Edge> removedEdges;


Graph Graph::copy() const{
    Graph graphCopy;
    for(auto v: vertexSet){
        graphCopy.addVertex(v->getStation());
    }
    for(auto v : vertexSet){
        int firstId = v->getId();
        for(Edge *e:v->getAdj()){
            Vertex *secondVertex = e->getDest();
            int secondId = secondVertex->getId();
            if(firstId < secondId){
                graphCopy.addBidirectionalEdge(v->getStation()->getName(),secondVertex->getStation()->getName(),e->getWeight(),e->getService());
            }
        }
    }
    return graphCopy;
}

int Graph::getNumVertex() const {
    return vertexSet.size();
}

int Graph::getNumEdge() const {
    int count = 0;
    for (auto v : vertexSet) {
        for (auto e : v->getAdj()) {
            count++;
        }
    }
    return count;
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
    Vertex* new_vertex = new Vertex(vertexSet.size()+1, station);
    vertexSet.push_back(new_vertex);
    vertexMap.insert({station->Name, new_vertex});
    return true;
}

void Graph::removeVertex(int id){
    auto v = findVertex(id);
    for(auto it = vertexSet.begin(); it != vertexSet.end(); it++){
        if(*it == v){
            vertexSet.erase( it);
            break;
        }
    }
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
    pairs.push_back(make_pair(key,value));
}

void Graph::addMunicipality(string municipio){
    municipios.insert(municipio);
}

void Graph::addDistrict(string distrito){
    distritos.insert(distrito);
}

bool Graph::addBidirectionalEdge(const string &sourc, const string &dest, int w, string service) {
    auto v1 = vertexMap[sourc];
    auto v2 = vertexMap[dest];
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w, service);
    auto e2 = v2->addEdge(v1, w, service);
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


int Graph::edmondsKarp(int source, int target) {
    int max = 0;
    Vertex* src = findVertex(source);
    Vertex*  dest = findVertex(target);
    if (src == nullptr || dest == nullptr || src == dest)
        return 0;

    //reset dos fluxos
    for (Vertex*  v : vertexSet)
        for (Edge* e : v->getAdj())
            e->setFlow(0);

    //encontrar caminhos de aumento de fluxo
    while (findAugmentingPath(src,dest)) {
        auto f = findMinResidualAlongPath(src, dest);
        augmentFlowAlongPath(src, dest, f);
        max+=f;
    }

    return max;
}

void Graph::max(){

    int maxAtual = -1, idA, idB;
    int flowMaximo;
    vector<pair<string, string>> maxPair;

    // Limpa o vetor de pares antes de iniciar a busca pelo máximo
    maxPair.clear();

    for (auto pair : pairs){

        int idA = getVertex(pair.first)->getId();
        int idB = getVertex(pair.second)->getId();

        flowMaximo = edmondsKarp(idA,idB);

        if(flowMaximo > maxAtual){

            // Atualiza o valor máximo e limpa o vetor de pares anteriores
            maxAtual = flowMaximo;
            maxPair.clear();
            maxPair.push_back(std::make_pair(pair.first, pair.second));
        }
        else if(flowMaximo == maxAtual){

            // Adiciona o novo par ao vetor de pares com valor máximo
            maxPair.push_back(std::make_pair(pair.first, pair.second));
        }
    }

    cout << "A(s) viagens que exigem mais comboios:" << endl;
    for(auto pair : maxPair){
        int idA = getVertex(pair.first)->getId();
        int idB = getVertex(pair.second)->getId();
        int flow = edmondsKarp(idA, idB);
        if(flow == maxAtual){
            cout << pair.first << " com destino a " << pair.second << " com: " << maxAtual << endl;
        }
    }
}
Vertex* Graph::getVertex(string name) {
    for (auto vertex : vertexSet) {
        if (vertex->getName() == name) {
            return vertex;
        }
    }
    return nullptr;
}


set<Vertex*> Graph::getVerticesByMunicipality(const string &municipality,Graph &g) {
    set<Vertex*> result;
    set<string> result1;
    for (auto vertex : g.vertexSet) {
        if (vertex->getStation()->getMunicipality() == municipality && vertex->getStation()->getName() != "supersink") {
            result.insert(vertex);
            result1.insert(vertex->getStation()->getName());
        }
    }
    return result;
}

set<Vertex*> Graph::getVerticesByDistrict(const string &distrito,Graph &g) {
    set<Vertex*> result;
    for (auto vertex : g.vertexSet) {
        if (vertex->getStation()->getDistrict() == distrito && vertex->getStation()->getName() != "supersink") {
            result.insert(vertex);
        }
    }
    return result;
}

void Graph::createSuperSink(const string &name, Graph &g, bool is_mun) {
        Stations *station = new Stations();
        station->Name = "supersink";
        g.addVertex(station);
        for (auto vertex : is_mun? g.getVerticesByMunicipality(name,g) : g.getVerticesByDistrict(name,g)) {
            if (vertex->getStation()->getName() != "supersink") {
                g.addEdge(vertex->getName(), station->Name, INT_MAX, "");
            }
        }
}

set<Vertex*> Graph::getVerticesNotInMunicipality(const string &municipality, Graph &g) {
    set<Vertex*> result;
    for (auto vertex : g.vertexSet) {
        if (vertex->getStation()->Municipality != municipality && vertex->getStation()->Municipality != "resto" && vertex->getStation()->Name != "supersink") {
            result.insert(vertex);
        }
    }
    return result;
}

set<Vertex*> Graph::getVerticesNotInDistrict(const string &distrito, Graph &g) {
    set<Vertex*> result;
    for (auto vertex : g.vertexSet) {
        if (vertex->getStation()->District != distrito && vertex->getStation()->District != "resto" && vertex->getStation()->Name != "supersink") {
            result.insert(vertex);
        }
    }
    return result;
}

void Graph::createSuperSource(const string &name, Graph &g, bool is_mun) {

        Stations *station = new Stations();
        station->Name = "supersource";
        station->Municipality = "resto";
        g.addVertex(station);
        for (auto vertex: is_mun? g.getVerticesNotInMunicipality(name,g) : g.getVerticesNotInDistrict(name,g)) {
            if (vertex->getAdj().size() == g.minVertexAdjSize(g)){
                    if(is_mun? (vertex->getStation()->getMunicipality() != name) :  (vertex->getStation()->getDistrict() != name)){
                        g.addEdge(station->Name, vertex->getStation()->Name, INT_MAX, "");
                    }
                }
            }
        }


int Graph::minVertexAdjSize(Graph &g){
    int min = INT_MAX;
    for(auto v : g.vertexSet){
        if(v->getAdj().size() < min && v->getAdj().size() > 0){
            min = v->getAdj().size();
        }
    }
    return min;
}


bool Graph::cmp(const pair<string, int>& a, const pair<string, int>& b) {
    if (a.second != b.second) {
        return a.second > b.second;
    } else {
        return a.first < b.first;
    }
}


void Graph::sort(unordered_map<string, int>& maxFlowsMuni, int k){
    vector<pair<string, int> > A;

    for (auto& it : maxFlowsMuni) {
        A.push_back(it);
    }

    std::sort(A.begin(), A.end(), cmp);


    maxFlowsMuni.clear();

        for (auto &it: A) {
            if(k>0 && it.first != "") {
                k--;
                maxFlowsMuni.insert(std::make_pair(it.first, it.second));
                cout << it.first << " com flow de:  " << it.second << endl;
            }

        }
}

void Graph::percorrerMunicipios(int k, bool is_mun) {
    readFiles rf;
    Graph graph = rf.originalGraph();

    if (is_mun) {
        unordered_map<string, int> maxFlowsMuni;

        for (auto municipio: municipios) {
            if(municipio == "LISBOA")
                cout << endl;
            Graph g = rf.originalGraph();
            g.createSuperSource(municipio, g, is_mun);

            g.createSuperSink(municipio, g,  is_mun);

            int flow = g.edmondsKarp(g.vertexSet.size() - 1, g.vertexSet.size());
            maxFlowsMuni.insert(std::make_pair(municipio, flow));

        }

        sort(maxFlowsMuni, k);
    }
    else {

        unordered_map<string, int> maxFlowsDist;

        for (auto distrito: distritos) {

            Graph g = rf.originalGraph();
            g.createSuperSource(distrito, g, is_mun);

            g.createSuperSink(distrito, g, is_mun);

            int flow = g.edmondsKarp(g.vertexSet.size() - 1, g.vertexSet.size());
            maxFlowsDist.insert(std::make_pair(distrito, flow));

        }
        sort(maxFlowsDist, k);

    }
}
bool Graph::removeEdge(const int &source, const int &dest, Graph &g) {
    Vertex* src = g.findVertex(source);
    if(src == nullptr) {
        return false;
    }
    return src->removeEdge(dest);
}

void Graph::createSubgraph() {

    readFiles rf;
    Graph g = rf.originalGraph();

    srand(time(nullptr));

    int NEdgesRm = rand() % 4 + 1;

    for (int i = 0; i < NEdgesRm; i++) {

        int src = rand() % vertexSet.size();
        Vertex *source = findVertex(src);
        alteredSources.push_back(source);

        if (source->getAdj().size() < 1) continue;
        int rand2 = rand() % source->getAdj().size();
        Vertex *dest = source->getAdj()[rand2]->getDest();
        alteredTargets.push_back(dest);
        int target = dest->getId();
        source->getAdj()[rand2]->setSource(source);
        removedEdges.push_back(*source->getAdj()[rand2]);
        removeEdge(src, target, g);
    }

    for (int i = 0; i<removedEdges.size(); i++) {
        cout <<"Origem: " << removedEdges[i].getOrig()->getName() << " | Destino: "<< removedEdges[i].getDest()->getName() << endl;
    }
}
/*
void bubbleSortIncommings(std::vector<Vertex*>& v) {
    bool swapped = true;
    size_t n = v.size();

    while (swapped) {
        swapped = false;
        for (size_t i = 1; i < n; i++) {
            if (v[i - 1]->getIncoming().size() > v[i]->getIncoming().size()) {
                std::swap(v[i - 1], v[i]);
                swapped = true;
            }
        }
        n--;
    }
}

void bubbleSortAdj(std::vector<Vertex*>& v) {
    bool swapped = true;
    size_t n = v.size();

    while (swapped) {
        swapped = false;
        for (size_t i = 1; i < n; i++) {
            if (v[i - 1]->getAdj().size() > v[i]->getAdj().size()) {
                std::swap(v[i - 1], v[i]);
                swapped = true;
            }
        }
        n--;
    }
}

void Graph::bubbleSortAffected(std::vector<Vertex*>& v) {
    bool swapped = true;
    size_t n = v.size();

    while (swapped) {
        swapped = false;
        for (size_t i = 1; i < n; i++) {
            if (arrivingTrains(v[i-1]->getId()) > arrivingTrains(v[i]->getId())) {
                std::swap(v[i - 1], v[i]);
                swapped = true;
            }
        }
        n--;
    }

}
*/
vector<Vertex*> sort_equal(vector<int> numbers, vector<Vertex*> vertexes) {
    unordered_map<Vertex*, int> vertex_to_number;
    for (int i = 0; i < vertexes.size(); i++) {
        vertex_to_number[vertexes[i]] = numbers[i];
    }
    sort(numbers.begin(), numbers.end());

    vector<Vertex*> sorted_vertexes;
    for(int i = 0; i < vertexes.size(); i++) {
        sorted_vertexes.push_back();
    }
    return sorted_vertexes;
}

vector<Vertex*> Graph::affectedEach(string source, string target, int k) {

    readFiles rf;

    vector<int> originalRes;
    vector<int> removedRes;
    vector<int> diffs;
    vector<Vertex*> kthaffectedEach;
    Graph graph = rf.originalGraph();



    for (auto v : vertexSet) {
        int res1 = graph.arrivingTrains(v->getId(),graph);
        originalRes.push_back(res1);
    }

    Graph g = rf.originalGraph();

    Vertex* src = g.findSourceTarget(source);
    Vertex* dest = g.findSourceTarget(target);

    int idsrc = src->getId();
    int iddest = dest->getId();


    for (auto v : vertexSet) {
        g.removeEdge(idsrc, iddest,g);
        int res2 = g.arrivingTrains(v->getId(), g);
        removedRes.push_back(res2);
    }

    for (int i = 0; i<originalRes.size() ; i++) {
        if (originalRes[i] != removedRes[i]) {
            kthaffectedEach.push_back(vertexSet[i]);
            int diff = originalRes[i]- removedRes[i];
            diffs.push_back(diff);
        }
    }


    vector<Vertex*> sortedVertexes = sort_equal(diffs, kthaffectedEach);
    sortedVertexes.erase(std::unique(sortedVertexes.begin(), sortedVertexes.end()), sortedVertexes.end());
    sortedVertexes.erase(sortedVertexes.begin() + k, sortedVertexes.end());
    return sortedVertexes;
}


/*
vector<Vertex*> Graph::kthAfectedNodes(int k) {

    vector<Vertex*> affectedNodes;

    for (int i = 0; i<alteredTargets.size(); i++) {
        if (alteredTargets[i]->getIncoming().size() < 1) {
            affectedNodes.push_back(alteredTargets[i]);
            alteredTargets.erase(alteredTargets.begin() + i-1);
            i--;
        }
    }

    for (int j = 0; j<alteredSources.size(); j++) {
        if (alteredSources[j]->getAdj().size() < 1 ) {
            affectedNodes.push_back(alteredSources[j]);
            alteredSources.erase(alteredSources.begin() + j-1);
            j--;
        }
    }

    bubbleSortIncommings(alteredTargets);
    bubbleSortAdj(alteredSources);

    for (auto v : alteredTargets) {
        affectedNodes.push_back(v);
    }
    for (auto v : alteredSources) {
        affectedNodes.push_back(v);
    }
    affectedNodes.erase(std::unique(affectedNodes.begin(), affectedNodes.end()), affectedNodes.end());
    affectedNodes.erase(affectedNodes.begin() + k, affectedNodes.end());
    return affectedNodes;

}
*/

/*
void Graph::createSuperSourceV2(const int idA) {
    Stations* station = new Stations();
    station->Name = "supersource";
    station->Municipality = "resto";
    addVertex(station);
    for (auto vertex : vertexSet) {
        if (vertex->getId() != idA && vertex->getAdj().size() == 1){
            addEdge(station->Name, vertex->getStation()->Name, INT_MAX, "");
        }
    }
}
*/

void Graph::createSuperSourceV2(const int idA, Graph &g) {
    Stations* station = new Stations();
    station->Name = "supersource";
    station->Municipality = "resto";
    g.addVertex(station);
    for (auto vertex : g.vertexSet) {
        if (vertex->getId() != idA && vertex->getAdj().size() == minVertexAdjSize(g)){
            addEdge(station->Name, vertex->getStation()->Name, INT_MAX, "");
        }
    }
}


double Graph::arrivingTrains(int sink, Graph &g1){
    g1.createSuperSourceV2(sink, g1);
    double res = 0;
    g1.edmondsKarp(g1.vertexSet.size(), sink);
    auto v = g1.findVertex(sink);
    for (auto e: v->getIncoming()){
        res += e->getFlow();
    }
    readFiles rf;
    g1 = rf.originalGraph();
    return res;
}



void Graph::Dijkstra(int idA){
    for (auto v: vertexSet){
        v->setDist(INF);
        v->setPath(nullptr);
        v->setVisited(false);
    }

    Vertex* s = findVertex(idA);
    s->setDist(0);
    MutablePriorityQueue<Vertex> q;
    q.insert(s);
    while (!q.empty()){
        Vertex* v = q.extractMin();
        v->setVisited(true);
        for (Edge *e: v->getAdj()){
            if (e->getService() == "ALFA PENDULAR"){
                e->setPrice(4);
            }
            else if(e->getService() == "STANDARD"){
                e->setPrice(2);
            }
            Vertex *w = e->getDest();
            if (w->isVisited()) continue;
            double dist = v->getDist() + e->getPrice();
            double oldDist = w->getDist();
            if (dist < oldDist){
                w->setDist(dist);
                w->setPath(e);
                if (oldDist == INF){
                    q.insert(w);
                }
                else q.decreaseKey(w);
            }
        }
    }
}

double Graph::operationCost(int idA, int idB){
    auto v1 = findVertex(idA);
    auto v2 = findVertex(idB);
    Dijkstra(idA);
    double maxflow = INT_MAX;

    for (auto current = v2; current != v1;){
        Edge *e = current->getPath();
        if (e==nullptr) return 0;
        if (e->getWeight()){
            maxflow = e->getWeight();

        }
        current = e->getOrig();
    }

    return maxflow;
}
/*
void Graph::menu2_1(string A, string B){
    Vertex* vertexA;
    Vertex* vertexB;
    vertexA = getVertex(A);
    vertexB = getVertex(B);

    if(vertexA == nullptr) {
        cout << "A estação '" << A << "' não existe \n";
        return;
    }
    if(vertexB == nullptr) {
        cout << "A estação '" << B << "' não existe \n";
        return;
    }

    int flow = edmondsKarp(vertexA->getId(),vertexB->getId());

    cout << "O flow maximo entre " << A << " e " << B << " é " << flow << endl;
}

void Graph::menu2_4(string A){
    Vertex* vertex;
    vertex = getVertex(A);

    if(vertex == nullptr) {
        cout << "A estação '" << A << "'  não existe \n";
        return;
    }


    cout << "O máximo de comboios que pode chegar a " << A << " é " << arrivingTrains(vertex->getId()) << endl;

}
*/