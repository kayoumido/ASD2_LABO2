/*
 * File:   TopologicalSort.h
 * Author: Olivier Cuisenaire
 * Modified by: Robin Demarta, Loïc Dessaules, Doran Kayoumi
 *
 * Created on 08. octobre 2014, 14:07
 *
 * A implementer
 * Classe permettant le tri topologique d'un graphe oriente
 */

#ifndef ASD2_TopologicalSort_h
#define ASD2_TopologicalSort_h

#include "DirectedCycle.h"
#include <list>
#include <vector>
#include <exception>

#include "ParcoursEnProfondeur.h"

template < typename GraphType >
class TopologicalSort {
private:
	/* A DEFINIR */
    DFSIter<GraphType> dfs;
    std::vector<int> order;
public:
    /**
     * @brief Creates the DFS object and checks if the graph has cycle
     *        O(v)   v=vertex
     * @param g The graph on which the topological sort will be operated
     */
    TopologicalSort(const GraphType & g) : dfs(g) {
        /* A IMPLEMENTER */
        // Throw an exception if a cycle is found in the graph
        DirectedCycle<GraphType> dc(g);
        if(dc.HasCycle())
            throw GraphNotDAGException(dc.Cycle());
    }

    /**
     * @brief Gets the topological order of the vertices
     *        O(v + e)   v=vertex e=edge
     * @return A vector containing the vertices
     */
    const std::vector<int>& Order() {
        /* A IMPLEMENTER */
        dfs.visitGraph([](int){}, [&](int v){order.push_back(v);});
        return order;
    }
    
    //exception si le graphe n'est pas un DAG (Directed Acyclic Graph)
    class GraphNotDAGException : public std::exception {
        
    private:
        //indexes des sommets du cycle qui empeche le tris topologique
        const std::list<int> cycle;
        
    public:
        GraphNotDAGException(const std::list<int> cycle) noexcept : exception(), cycle(cycle) {
            
        }
        
        virtual const char* what() const noexcept {
            return "Topological sort impossible : the graph is not a DAG";
        }
        
        const std::list<int>& Cycle() const noexcept {
            return cycle;
        }
    };
};


#endif
