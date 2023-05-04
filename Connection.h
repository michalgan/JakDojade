#ifndef JAKDOJADE_CONNECTION_H
#define JAKDOJADE_CONNECTION_H
#include "String.h"
class String;

struct Connection {
    Connection(String &departure, String &origin, int time): departure(departure), origin(origin), time(time){}
    void print() const{
        departure.print();
        printf(" ");
        origin.print();
        printf(" %d\n", time);
    }
    String departure;
    String origin;
    int time;
};


#endif //JAKDOJADE_CONNECTION_H
