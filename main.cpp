/*
 * File:   DFSOrder.h
 * Author: Cuisenaire
 * Modified by: Robin Demarta, Loïc Dessaules, Doran Kayoumi
 * Labo 2
 * Created on 3. novembre 2014, 08:23
 */


#include <cstdlib>
#include <iostream>
#include "Util.h"
#include "DiGraph.h"
#include "SymbolGraph.h"
#include "TopologicalSort.h"

using namespace std;

//methode permettant de verifier le graphe trie par rapport au fichier d'entree
bool checkOrder(const std::vector<int>& order,
                const SymbolGraph<DiGraph>& SG,
                const std::string& filename,
                char delim) {

    std::vector<int> positionInOrder(order.size());
    for( size_t i = 0; i < order.size(); ++i )
        positionInOrder[order[i]] = int(i);

    bool ok = true;

    std::string line;

    std::ifstream s(filename);
    while (std::getline(s, line))
    {
        auto names = split(line,delim);

        for(size_t i = 1; i < names.size(); ++i) {

            int v = SG.index(names[0]); // module
            int w = SG.index(names[i]); // ieme prerequis

            if ( positionInOrder[ v ] < positionInOrder [ w ]) {
                cout << "Erreur d'ordre : " << names[0] << " avant " << names[i] << endl;
                ok = false;
            }
        }
    }
    s.close();

    return ok;
}

/**
 * @brief Tests the topological sort and cycle detection functions
 * @param fileName Path to the file containing the graph
 * @param delimiter Character that separates the vertices in the file
 */
void testTriTopologique(string fileName, char delimiter) {
    SymbolGraph<DiGraph> SG(fileName, delimiter);

    try {
        // Topological sort
        TopologicalSort<DiGraph> ts(SG.G());
        const vector<int>& order = ts.Order();

        // Topological sort display
        cout << fileName << " est un DAG" << endl << "Ordre topologique:" << endl;
        for(int i : order){
            cout << SG.symbol(i) << " ";
        }
        cout << endl;

        // Verification using the checkOrder function
        if(checkOrder(order, SG, fileName, delimiter)) {
            cout << "Verification reussie" << endl;
        } else {
            cout << "Verification echouee" << endl;
        }
    } catch(TopologicalSort<DiGraph>::GraphNotDAGException& e) {
        // Cycle found -> display
        cout << fileName << " n'est pas un DAG" << endl << "Cycle trouve:" << endl;
        for(int v : e.Cycle()) {
            cout << SG.symbol(v) << " ";
        }
        cout << endl;
    }
}

int main(int argc, const char * argv[]) {
    /* A IMPLEMENTER */
    const char DELIMITER = ',';
    testTriTopologique("prerequis.txt", DELIMITER); // Test topological sort and cycle detection on a graph without cycles
    cout << endl;
    testTriTopologique("prerequis2.txt", DELIMITER); // Test topological sort and cycle detection on a graph with cycles


    return EXIT_SUCCESS;
}
