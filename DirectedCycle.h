/*
 * File:   DirectedCycle.h
 * Author: Olivier Cuisenaire
 * Created on 08. octobre 2014, 10:46
 *
 * A implementer
 * Classe permettant la detection de cycle sur un graphe oriente
 */

#ifndef ASD2_DirectedCycle_h
#define ASD2_DirectedCycle_h

#include <vector>
#include <algorithm>

typedef int Vertex;

template<typename GraphType>
class DirectedCycle {
private:
    const GraphType& g;
    std::vector<bool> marked;
    std::vector<bool> stacked;
    bool cycleFound;
    Vertex endOfCycle;
    std::list<Vertex> cycle;

    void cycleDetection(Vertex v) {
        marked.at(v) = true;
        stacked.at(v) = true;

        for (auto w : g.adjacent(v)) {
            if (cycleFound) {
                return;
            } else if (!marked.at(w)) {
                cycleDetection(w);
            } else if (stacked.at(w)) {
                cycleFound = true;
                endOfCycle = w;
                cycle.push_back(w);
            }
        }

        if(!cycleFound) {
            stacked.at(v) = false;
        }else{
            if (endOfCycle != -1) {
                cycle.push_back(v);
                if (endOfCycle == v){
                    endOfCycle = -1;
                }
            }
        }
    }

public:
    //constructeur
    DirectedCycle(const GraphType &G) : g(G) {
        marked.resize(g.V());
        stacked.resize(g.V());
        cycleFound = false;
        endOfCycle = -1;
    }

    //indique la presence d'un cycle
    bool HasCycle() {
        for (int i = 0; i < stacked.size(); ++i) {
            if(cycleFound){
                break;
            }
            cycleDetection(i);
        }

        return cycleFound;
    }

    //liste les indexes des sommets formant une boucle
    std::list<int> Cycle() {
        cycle.reverse();
        return cycle;
    }

};

#endif
