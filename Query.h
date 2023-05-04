//
// Created by micha on 4/27/2023.
//

#ifndef JAKDOJADE_QUERY_H
#define JAKDOJADE_QUERY_H


#include "String.h"
class String;


struct Query {
    Query(String& departure, String& origin, int mode): departure(departure), origin(origin), mode(mode){}
    void print() const{
        departure.print();
        printf(" ");
        origin.print();
        printf(" %d\n", mode);
    }
    String departure;
    String origin;
    int mode;
};


#endif //JAKDOJADE_QUERY_H
