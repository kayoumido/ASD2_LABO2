/* 
 * File:   SymbolGraph.h
 * Author: Olivier Cuisenaire
 * Modified: Valentin Minder (2018), Raphael Racine (2018), APB (2019)
 *
 * Created on 26. septembre 2014, 15:08
 */

#ifndef SYMBOLGRAPH_H
#define SYMBOLGRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

#include "Util.h"

template<typename GraphType>
class SymbolGraph
{
    typedef GraphType Graph; 
private:
    std::map<std::string,int> symbolTable;
    std::vector<std::string> keys;
    Graph* g;
    
public:
    
    ~SymbolGraph()
    {
        delete g; 
    }            
    
    //creation du SymbolGraph a partir du fichier
    SymbolGraph(const std::string& filename, char delim = '/') {   
      
        // lecture du fichier, ligne par ligne puis 
        // element par element (separes par delim)

        std::string line;
        int cnt=0; 

        std::ifstream s(filename);
        while (std::getline(s, line))
        {
            auto names = split(line, delim);
            for( auto name : names ) 
                if(!contains(name))
                    symbolTable[name] = cnt++;
        }
        s.close();
        
        keys.resize(cnt);
        for(const auto& pair : symbolTable)
            keys[pair.second] = pair.first; 
        
        g = new Graph(cnt);
        
        s.open(filename);
        while (std::getline(s, line))
        {
            auto names = split(line, delim);
           
            int v = symbolTable[names[0]];
            for(size_t i = 1; i < names.size(); ++i ) {
                int w = symbolTable[names[i]];
                g->addEdge(v,w);
            }
        }
        s.close();
        
    }
    
    //verifie la presence d'un symbole
    bool contains(const std::string& name) const {
        return symbolTable.find(name) != symbolTable.end();
    }
    
    //index du sommet correspondant au symbole
    int index(const std::string& name) const {
        return symbolTable.at(name);
    }
    
    //symbole correspondant au sommet
    std::string symbol(int idx) const {
        return keys[idx];
    }

    // retourne les symboles adjacents à un symbole
    std::vector<std::string> adjacent(const std::string & symbol) const
    {
        if(!contains(symbol))
            return std::vector<std::string>(0);
        
        // les idx adjacents a l'idx de symbol
        auto& adjIdx = g->adjacent( index(symbol));

        std::vector<std::string> adjStr(adjIdx.size());
        
        // transformation en symboles de la liste d'idx adjacents
        for (auto adjId : adjIdx) {
            adjStr.push_back(this->name(adjId));
        }
        
        return adjStr; 
    }
    
    const Graph& G() const {
        return *g; 
    }
    
};


#endif	/* SYMBOLGRAPH_H */
