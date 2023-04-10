#include <iostream>
#include "Graph.h"
#include "network.h"
#include "readFiles.h"
#include <sstream>
#include <fstream>
#include <unordered_set>

/*void createEdges(Graph &g){
    ifstream myFile;
    string currentLine;
    myFile.open("../network2.csv");
    getline(myFile, currentLine);
    set<pair<string,string>> set_network;
    string tempString;
    int inputInt = 1;
    while (getline(myFile, currentLine)) {
        Network *viagem = new Network();
        stringstream inputString(currentLine);
        getline(inputString, viagem->Source, ',');
        if (viagem->Source.front() == '\"') {
            string completeSource = viagem->Source;
            while (completeSource.back() != '\"' && getline(inputString, viagem->Source, ',')) {
                completeSource += "," + viagem->Source;
            }
            completeSource.erase(0, 1);
            completeSource.erase(completeSource.size() - 1);
            viagem->Source = completeSource;
        }
        getline(inputString, viagem->Target, ',');
        if (viagem->Target.front() == '\"') {
            string completeTarget = viagem->Target;
            while (completeTarget.back() != '\"' && getline(inputString, viagem->Target, ',')) {
                completeTarget += "," + viagem->Target;
            }
            completeTarget.erase(0, 1);
            completeTarget.erase(completeTarget.size() - 1);
            viagem->Target = completeTarget;
        }
        g.addPair(viagem->Source, viagem->Target);
        getline(inputString, tempString, ',');
        inputInt = stoi(tempString);
        viagem->Capacity = inputInt;
        getline(inputString, viagem->Service, ',');
        if ((set_network.insert(std::make_pair(viagem->Source, viagem->Target)).second)) {
            g.addBidirectionalEdge(viagem->Source, viagem->Target, viagem->Capacity, viagem->Service);
        }
    }
    myFile.close();
}

void createVertexes(Graph &g){
    ifstream myFile;
    string currentLine;

    unordered_set<string> set_stations;

    myFile.open("../stations2.csv");
    getline(myFile, currentLine);    // ignore first line
    while (getline(myFile, currentLine)) {
        Stations* station = new Stations();
        stringstream iss(currentLine);
        getline(iss, station->Name, ',');
        if (station->Name.front() == '\"') {
            std::string completeName = station->Name;
            while (completeName.back() != '\"' && getline(iss, station->Name, ',')) {
                completeName += "," + station->Name;
            }
            completeName.erase(0, 1);  // remove leading quote
            completeName.erase(completeName.size() - 1);  // remove trailing quote
            station->Name = completeName;
        }

        getline(iss, station->District, ',');
        getline(iss, station->Municipality, ',');
        getline(iss, station->Township, ',');
        if (station->Township.front() == '\"') {
            std::string completeTownship = station->Township;
            while (completeTownship.back() != '\"' && getline(iss, station->Township, ',')) {
                completeTownship += "," + station->Township;
            }
            completeTownship.erase(0, 1);  // remove leading quote
            completeTownship.erase(completeTownship.size() - 1);  // remove trailing quote
            station->Township = completeTownship;
        }
        g.addMunicipality(station->Municipality);
        g.addDistrict(station->District);
        getline(iss, station->Line, ',');
        if((set_stations.insert(station->Name).second)){
            g.addVertex(station);
    }
    }
    myFile.close();

}*/

/*
void Menu4 (Graph g) {
    int num = 0;
    g.createSubgraph();
    cout << "Choose a number os affected stations: ";
    cin >> num;
    vector<Vertex*> affectedNodes = g.kthAfectedNodes(num);
    cout << "The stations that are most affected by the management of the lines are: " << endl;
    for (auto v : affectedNodes) {
        cout << v->getName() << endl;
    }
}
*/


int main() {
    readFiles rf;
    Graph g = rf.originalGraph();
    g.createSubgraph();
    string s;
    string d;
    cin >> s;
    cin >> d;
    vector<Vertex*> aff = g.affectedEach(s,d,5);
    for (int i = 0; i<aff.size(); i++) {
        cout << aff[i]->getName() << endl;
    }

    //Graph subgraph;
    //readFiles rf;
    //g = rf.originalGraph();
    //createVertexes(g);
    //createEdges(g);

    //string stringResposta;
    //std::cout << g.getNumVertex() << std::endl;
    //std::cout << g.getNumEdge() << std::endl;
    //subgraph = g.createSubgraph();
    //std::cout << subgraph.getNumVertex() << std::endl;
    //std::cout << subgraph.getNumEdge() << std::endl;
    //std::cout << g.arrivingTrains(5) << std::endl;
    //std::cout << g.operationCost(9,74) << std::endl;
    //Menu4(subgraph);
    //g.max();
    //g.maxFlow(0,3);
    //g.percorrerMunicipios(10,false);
    //std::cout << g.getVertexSet().size() << std::endl;


/*
    while (stringResposta != "q") {
        cout << "===================================== MENU ========================================" << endl;
        cout << "Maximo flow entre duas estações? - [PRESS 1]" << endl;
        cout << "Verificar o máximo flow entre todos os pares de estações? - [PRESS 2]" << endl;
        cout << "Verificar o Top-K distritos / municipios quanto à sua necessidade? - [PRESS 3]" << endl;
        cout << "Maximo de comboios que pode chegar a uma estacao? - [PRESS 4]" << endl;
        cout << "Maximo flow entre duas estacoes tendo em conta o minimo custo? - [PRESS 5]" << endl;
        cout << " - [PRESS 6]" << endl;
        cout << " - [PRESS 7]" << endl;
        cout << " - [PRESS 8]" << endl;

        cout << " - [PRESS q]" << endl;
        cout << "==================================================================================" << endl;
        cin >> stringResposta;
        cin.ignore();
        if (stringResposta == "q") {
            break;
        }
        if (stringResposta == "1") {
            while (stringResposta != "e") {
                cout << "============================ MENU ================================" << endl;
                cout << "Digite o nome da primeira estação | Exemplo: Estarreja" << endl;
                getline(cin, stringResposta);
                string primeira = stringResposta;
                cout << "Digite o nome da segunda estação | Exemplo: Luz" << endl;
                getline(cin, stringResposta);
                string segunda = stringResposta;
                g.menu2_1(primeira, segunda);
                cout << "Voltar para tras - [PRESS e] " << endl << "Para repetir - [PRESS 1]" << endl;
                cout << "==================================================================" << endl;
                cin >> stringResposta;
                if (stringResposta == "e") break;
                cin.ignore();
            }
        }
        if (stringResposta == "2") {
            while (stringResposta != "e") {
                cout << "============================ MENU ================================" << endl;
                g.max();
                cout << "Voltar para tras - [PRESS e] " << endl << "Para repetir - [PRESS 2]" << endl;
                cout << "==================================================================" << endl;
                cin >> stringResposta;
                if (stringResposta == "e") break;
                cin.ignore();
            }
        }
        if (stringResposta == "3") {
            while (stringResposta != "e") {
                cout << "============================ MENU ================================" << endl;
                cout << "Qual o top K? | Digite o K: " << endl;
                cin >> stringResposta;
                int k = stoi(stringResposta);
                cout << "Top-k distritos ou municipios? | 0 - Distritos | 1 - Municipios " << endl;
                cin >> stringResposta;
                bool is_mun = stoi(stringResposta);
                g.percorrerMunicipios(k, is_mun);
                cout << "Voltar para tras - [PRESS e] " << endl << "Para repetir - [PRESS 3]" << endl;
                cout << "==================================================================" << endl;
                cin >> stringResposta;
                if (stringResposta == "e") break;
                cin.ignore();
            }
        }
        if (stringResposta == "4") {
            while (stringResposta != "e") {
                cout << "============================ MENU ================================" << endl;
                cout << "Qual a estacao que deseja verificar? | Exemplo: Estarreja" << endl;
                getline(cin, stringResposta);
                g.menu2_4(stringResposta);
                cout << "Voltar para tras - [PRESS e] " << endl << "Para repetir - [PRESS 4]" << endl;
                cout << "==================================================================" << endl;
                cin >> stringResposta;
                if (stringResposta == "e") break;
                cin.ignore();
            }
        }
        if (stringResposta == "5") {
            while (stringResposta != "e") {
                cout << "============================ MENU ================================" << endl;
                cout << "Digite o nome da primeira estação | Exemplo: Estarreja" << endl;
                getline(cin, stringResposta);
                string primeira = stringResposta;
                cout << "Digite o nome da segunda estação | Exemplo: Luz" << endl;
                getline(cin, stringResposta);
                string segunda = stringResposta;

                //chamar a tua função, verifica se precisas de func auxiliar como por exemplo a 2.4
                // se precisares vais usar o getVertex quase de certeza e depois cout

                cout << "Voltar para tras - [PRESS e] " << endl << "Para repetir - [PRESS 1]" << endl;
                cout << "==================================================================" << endl;
                cin >> stringResposta;
                if (stringResposta == "e") break;
            }
        }
        if (stringResposta == "6") {}
        if (stringResposta == "7") {}


    }
*/

    return 0;
}
