//
// Created by micha on 4/30/2023.
//

#ifndef JAKDOJADE_VERTEX_H
#define JAKDOJADE_VERTEX_H


#include "List.h"
#include "Coordinates.h"
struct Coordinates;


struct Vertex {
    explicit Vertex(Coordinates position): position(position){
        neighbours = List<Vertex*>();
        edges = List<Edge*>();
    }
    Coordinates position;
    List<Vertex*> neighbours;
    List<Edge*> edges;
};


#endif //JAKDOJADE_VERTEX_H
