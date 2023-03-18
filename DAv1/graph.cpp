//
// Created by Daniel on 07/03/2023.
//

#include "graph.h"
#include "queue"
#include "set"
#include "vector"
#include "NodesEdges.h"
#include "list"


// Constructor: nr nodes and direction (default: undirected)

void bfs(int v);

graph::graph(int num, bool dir) : n(num), hasDir(dir), nodes(num + 1) {
}

/*
// Add edge from source to destination with a certain weight
void graph::addEdge(int src, int dest, trip trips) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].getAdj().push_back({dest, trips});
    if (!hasDir) nodes[dest].getAdj().push_back({src, trips});

}
 */

void graph::addEdge(int src, int dest, trip trips) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].getAdj().push_back(std::make_pair(dest, trips));
    if (!hasDir) nodes[dest].getAdj().push_back(std::make_pair(src, trips));
}
/*
// Depth-First Search: example implementation
int Graph::dfs(int v) {
    cout << v << " "; // show node order
    int count = 1;
    nodes[v].visited = true;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited) {
            count += dfs(w);
        }
    }
    return count;
}
 */

void graph::vetorToGraph(set<trip *>& tripsVec, set<stations *>& stationsVec){
    int i=0;
    int j = 1;
    auto station_it = stationsVec.begin();
    auto trips_it = tripsVec.begin();
    for (auto it = nodes.begin() + 1; it != nodes.end(); it++, station_it++) {
        it->setStation(*(*station_it));

    }
    int tripSource=0;
    int tripTarget=0;

    for(auto it = tripsVec.begin(); it != tripsVec.end(); it++){
        for(auto itt = stationsVec.begin(); itt != stationsVec.end(); itt++){
            if ((*it)->getSource() == (*itt)->getName()){
                tripSource = j;

            }
            if ((*it)->getTarget()==(*itt)->getName()){
                tripTarget = j;
            }
            j++;
        }
        addEdge(tripSource,tripTarget,*(*trips_it));
        trips_it++;
    }
}



void graph::bfs(int v) {
    int curr = 0;
    for (int i=1; i<=n; i++) nodes[i].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].visited = true;
    nodes[v].distance = curr;
    queue<string> currPath;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        curr = nodes[u].distance;
        // show node order (tá mal)
        //cout << nodes[u].eAirport.Name << " ";
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].distance = curr + 1;
            }
        }
    }
}

void graph::setPath(Edge *path) {
    this->path = path;
}

void graph::testAndVisit(std::queue<Node>& queue, Edge e, struct Node w, double residual){
    if (!w.visited && residual > 0) {
        w.visited = true;
        //w->setPath(e);
        w.path = &e;
        queue.push(w);
    }
}


bool graph::findAugmentingPath(Node src, Node dest){
    for (Node  v : nodes) //se trocarmos de vector para set, trocar aqui
        v.visited = false;

    src.visited = true;

    std::queue<Node> queue;
    queue.push(src);

    while (!queue.empty() && !dest.visited){
        Node v = queue.front();
        queue.pop();

        for (Edge e: v.adj)
            testAndVisit(queue,e,e.dest,e.cTrip.Capacity-e->getFlow());

        for (Edge e: v->getIncoming())
            testAndVisit(queue,e,e->getOrig(),e->getFlow());
    }

    return dest.visited;
}

double graph::findMinResidualAlongPath(Node src, Node dest){
    double f = INF;
    for(Node v = dest; v != src;){
        Edge e = v->getPath();
        if (e->getDest() == v){
            f = std::min(f, e.cTrip.Capacity -e->getFlow());
            v = e->getOrig();
        }
        else{
            f = std::min(f,e->getFlow());
            v = e->getDest();
        }
    }
    return f;
}

void graph::augmentFlowAlongPath(Node src, Node dest, double f){
    for (Node v = dest; v != src;){
        Edge e = v->getPath();
        double flow = e->getFlow();

        //capacidade residual
        if (e.dest == v){
            e->setFlow(flow+f);
            v = e->getOrig();
        }

            //fluxo no sentido oposto
        else{
            e->setFlow(flow-f);
            v = e.dest;
        }
    }
}


void graph::edmondsKarp(int source, int target) {
    Node src = findVertex(source);
    Node  dest = findVertex(target);
    if (src == nullptr || dest == nullptr || src == dest)
        return;

    //reset dos fluxos
    for (Node  v : nodes)
        for (Edge e : v.adj)
            e->setFlow(0);

    //encontrar caminhos de aumento de fluxo
    while (findAugmentingPath(src,dest)) {
        auto f = findMinResidualAlongPath(src, dest);
        augmegraphwAlongPath(src, dest, f);
    }
}

Node graph::findNode(string){
    for (auto n : nodes)
        if (n.c == id)
            return v;
    return nullptr;
}


