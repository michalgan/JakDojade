#include "String.h"
#include "Connection.h"
#include "Query.h"
#include "Navigator.h"

#define BUFFER 3000

class String;
struct Connection;
struct Query;
class Navigator;

Navigator inputData(){
    // loading map
    int sizeY, sizeX;
    scanf("%d %d\n", &sizeX, &sizeY);
    char * temp = new char[BUFFER];
    char ** map = new char * [sizeY];
    for (int y = 0; y < sizeY; ++y) {
        scanf("%s\n", temp);
        map[y] = new char[sizeX];
        for (int x = 0; x < sizeX; ++x) {
            map[y][x] = temp[x];
        }
    }

    // loading air connections
    int nOfAirConnections;
    scanf("%d\n", &nOfAirConnections);
    char * tempDeparture = new char[BUFFER];
    char * tempOrigin = new char[BUFFER];
    int time;
    auto airConnections = new List<Connection*>();
    for (int i = 0; i < nOfAirConnections; ++i) {
        scanf("%s %s %d\n", tempDeparture, tempOrigin, &time);
        String departure = String(tempDeparture);
        String origin = String(tempOrigin);
        airConnections->append(new Connection(origin, departure, time));
    }

    // loading queries
    int nOfQueries;
    auto queries = new List<Query>();
    scanf("%d\n", &nOfQueries);
    int mode;
    for (int i = 0; i < nOfQueries; ++i) {
        scanf("%s %s %d\n", tempDeparture, tempOrigin, &mode);
        String departure = String(tempDeparture);
        String origin = String(tempOrigin);
        queries->append(Query(departure, origin, mode));
    }
    delete[] temp;
    delete[] tempOrigin;
    delete[] tempDeparture;
    return Navigator(sizeY, sizeX, map, airConnections, queries);
}
int main() {
    Navigator navigator = inputData();
//    navigator.printMap();
//    navigator.printConnections();
//    navigator.printCities();
//    navigator.printQueries();
    navigator.executeQueries();
    return 0;
}
