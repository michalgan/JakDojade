//
// Created by micha on 4/27/2023.
//

#ifndef JAKDOJADE_CITY_H
#define JAKDOJADE_CITY_H


#include "String.h"
#include "Coordinates.h"
class String;
struct Coordinates;


struct City {
    City(String& name, int y, int x): name(name), position(y, x){}
    void print() const{
        name.print();
        printf("(%d,%d)\n", position.y, position.x);
    }
    String name;
    Coordinates position;
};


#endif //JAKDOJADE_CITY_H
