//
// Created by micha on 4/27/2023.
//

#ifndef JAKDOJADE_NAVIGATOR_H
#define JAKDOJADE_NAVIGATOR_H

#include "City.h"
#include "Connection.h"
#include "Query.h"
#include "Coordinates.h"
#include "Edge.h"
#include "Graph.h"

struct Connection;
struct Query;
struct Coordinates;
struct City;
struct Edge;
struct Graph;
class Navigator {
public:
    Navigator(int sizeY, int sizeX, char ** map, List<Connection*> * airConnections, List<Query> * queries);
    int getSizeY() const;
    int getSizeX() const;
    bool coordsValid(int y, int x) const;
    int countAdjoiningRoads(int y, int x);
    void findCrossroads();
    String& findCityName(int cityY, int cityX);
    void findCities();
    Coordinates * findUnvisitedAdjoiningRoad(int y, int x, bool ** visited);
    void findConnections();
    void findEdgesFromPoint(int startY, int startX, bool ** visited);
    City * findCityByName(const String& name);
    void executeQueries();
    void printCities();
    void printConnections();
    void printQueries();
    void printCrossroads();
    void printMap();
    void printEdges();void printPath(int currentVertex, int * parents);
    void printSolution(int startVertex,  int * distances, int * parents, int nVertices);
    void calculateTime(int endVertex,  int * distances, int * parents, int mode);
    void dijkstra(Graph& graph, int startVertex, int endVertex, int mode);
    void optimizeMap();
    bool uselessTile(int y, int x);
    bool isCity(int y, int x);
    ~Navigator();
    static bool isLetterOrNumber(char c);
    static char type(char c);
private:
    int sizeY;
    int sizeX;
    char ** map;
    List<Connection*> * airConnections;
    List<Query> * queries;
    List<Coordinates> crossroads;
    List<Connection*> connections;
    List<City*> cities;
    List<Edge*> edges;
    Graph * navigationMap;
    constexpr static const char uselessRoadsPatterns[20][3][3] = {
        {
            {'r','r','r'},
            {'c','r','c'},
            {'c','c','c'}
        },
        {
                {'r','c','c'},
                {'r','r','c'},
                {'r','c','c'}
        },
        {
                {'c','c','c'},
                {'c','r','c'},
                {'r','r','r'}
        },
        {
                {'c','c','r'},
                {'c','r','r'},
                {'c','c','r'}
        },
        {
                {'c','r','r'},
                {'c','r','r'},
                {'c','c','c'}
        },
        {
                {'c','c','c'},
                {'c','r','r'},
                {'c','r','r'}
        },
        {
                {'r','r','c'},
                {'r','r','c'},
                {'c','c','c'}
        },
        {
                {'c','c','c'},
                {'r','r','c'},
                {'r','r','c'}
        },
        {
                {'r','r','c'},
                {'r','r','c'},
                {'r','r','c'}
        },
        {
                {'c','r','r'},
                {'c','r','r'},
                {'c','r','r'}
        },
        {
                {'r','r','r'},
                {'r','r','r'},
                {'c','c','c'}
        },
        {
                {'c','c','c'},
                {'r','r','r'},
                {'r','r','r'}
        },
        {
                {'r','c','c'},
                {'r','r','c'},
                {'r','r','c'}
        },
        {
                {'c','c','c'},
                {'r','r','c'},
                {'r','r','r'}
        },
        {
                {'r','r','r'},
                {'r','r','c'},
                {'c','c','c'}
        },
        {
                {'r','r','c'},
                {'r','r','c'},
                {'r','c','c'}
        },
        {
                {'c','r','r'},
                {'c','r','r'},
                {'c','c','r'}
        },
        {
                {'r','r','r'},
                {'c','r','r'},
                {'c','c','c'}
        },
        {
                {'c','c','c'},
                {'c','r','r'},
                {'r','r','r'}
        },
        {
                {'c','c','r'},
                {'c','r','r'},
                {'c','r','r'}
        }
    };
};


#endif //JAKDOJADE_NAVIGATOR_H