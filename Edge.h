//
// Created by micha on 4/28/2023.
//

#ifndef JAKDOJADE_EDGE_H
#define JAKDOJADE_EDGE_H


#include <cstdio>
#include "Coordinates.h"
struct Coordinates;


struct Edge {
    Edge(Coordinates start, Coordinates end, int wage, bool bothDirections): start(start), end(end), wage(wage), bothDirections(bothDirections){}
    void print() const{
        printf("(%d,%d) -> (%d) -> (%d,%d)\n", start.y, start.x, wage, end.y, end.x);
    }
    Coordinates start;
    Coordinates end;
    int wage;
    bool bothDirections;
};


#endif //JAKDOJADE_EDGE_H
