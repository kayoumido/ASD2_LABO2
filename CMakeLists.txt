cmake_minimum_required(VERSION 3.14)
project(Labo02)

set(CMAKE_CXX_STANDARD 11)

add_executable(Labo02 main.cpp DiGraph.cpp DiGraph.h DirectedCycle.h ParcoursEnProfondeur.h SymbolGraph.h TopologicalSort.h Util.h Util.cpp)