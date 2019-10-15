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
    Vertex endOfCycle; // The vertex that is the end (also begin) of the cycle
    std::list<Vertex> cycle;

    /**
     * @brief Launch a cycle detection from a specific Vertex.
     *        O(v + e)   v=vertex e=edge
     * @param v The Vertex from which we want to detect a cycle
     */
    void cycleDetection(Vertex v) {
        marked.at(v) = true;
        stacked.at(v) = true;

        // Loop trough adjacent of the current vertex
        for (auto w : g.adjacent(v)) {
            // Cycle found, stop the detection and go out the recursion call
            if (cycleFound) {
                return;
            }
            // Not already marked -> launch the cycle detection for the current adjacent vertex
            else if (!marked.at(w)) {
                cycleDetection(w);
            }
            // Vertex already appears in the stacked vector -> cycle detected
            else if (stacked.at(w)) {
                cycleFound = true;
                endOfCycle = w;
                cycle.push_back(w);
            }
        }

        if(!cycleFound) {
            stacked.at(v) = false;
        }else{
            // We know the end of cycle
            if (endOfCycle != -1) {
                // We can push the current vertex to our list, to recreate the cycle
                cycle.push_back(v);
                // The current vertex is the same vertex as the end of cycle => we reached the end of the cycle
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

        // Launch (if no cycle already found) the cycle detection from each vertex
        for (int i = 0; i < g.V(); ++i) {
            if(cycleFound){
                break;
            }
            cycleDetection(i);
        }
    }

    /**
     * @brief Check if the Graph contains a cycle
     *        O(v)   v=vertex
     * @return True if the Graph contains a cycle, false otherwise
     */
    bool HasCycle() {
        return cycleFound;
    }

    /**
     * @brief Return the vertexes list of the cycle
     *         O(n) Because we have a display following the arrows direction of the cycle (a -> b -> c -> a)
     *         ( O(1) if we decide to remove the reverse and only display the vertex contains in the cycle)
     * @return A list contains each vertex in the cycle
     */
    std::list<int> Cycle() {
        cycle.reverse();
        return cycle;
    }

};

#endif
