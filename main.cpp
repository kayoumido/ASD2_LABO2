/*
 * File:   DFSOrder.h
 * Author: Cuisenaire
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

void testTriTopologique(string fileName, char delimiter) {
    SymbolGraph<DiGraph> SG("prerequis.txt", ',');

    try {
        // Tri topologique
        TopologicalSort<DiGraph> ts(SG.G());
        const vector<int>& order = ts.Order();

        // Affichage tri
        cout << fileName << " est un DAG" << endl << "Ordre topologique:" << endl;
        for(int i : order){
            cout << SG.symbol(i) << " ";
        }
        cout << endl;

        // Vérification
        if(checkOrder(order, SG, fileName, delimiter)) {
            cout << "Verification reussie" << endl;
        } else {
            cout << "Verification echouee" << endl;
        }
    } catch(TopologicalSort<DiGraph>::GraphNotDAGException& e) {
        // Cycle trouvé -> afficher
        cout << fileName << " n'est pas un DAG" << endl << "Cycle trouve:" << endl;
        for(int v : e.Cycle()) {
            cout << v << " ";
        }
        cout << endl;
    }
}

int main(int argc, const char * argv[]) {
    /* A IMPLEMENTER */
    const char DELIMITER = ',';

    testTriTopologique("prerequis.txt", DELIMITER);
    cout << endl;
    testTriTopologique("prerequis2.txt", DELIMITER);

    return EXIT_SUCCESS;
}
