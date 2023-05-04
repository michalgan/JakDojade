//
// Created by micha on 4/27/2023.
//

#include "Navigator.h"
Navigator::Navigator(int sizeY, int sizeX, char ** map, List<Connection*> * airConnections, List<Query> * queries):
        sizeY(sizeY), sizeX(sizeX), map(map), airConnections(airConnections), queries(queries){
    crossroads = List<Coordinates>();
    connections = List<Connection*>();
    edges = List<Edge*>();
    findCities();
    optimizeMap();
    findCrossroads();
    findConnections();
    navigationMap = new Graph(cities.size() + crossroads.size(), edges);

}
int Navigator::getSizeY() const{
    return sizeY;

}
int Navigator::getSizeX() const{
    return sizeX;

}
bool Navigator::coordsValid(int y, int x) const{
    return x >= 0 && y >= 0 && x < sizeX && y < sizeY;

}
int Navigator::countAdjoiningRoads(int y, int x){
    if(coordsValid(y, x)) {
        int counter = 0;
        int coords[4][2] = { {y-1, x
                             },  {y, x-1
                             },  {y+1, x
                             },  {y, x+1
                             }
        };
        for(auto coord : coords){
            y = coord[0];
            x = coord[1];
            if(coordsValid(y, x) && (map[y][x] == '#' || map[y][x] == 'x' || map[y][x] == '*'))
                counter += 1;

        }
        return counter;

    }
    else
        return -1;

}
void Navigator::findCrossroads(){
    for (int y = 0; y < sizeY; ++y) {
        for (int x = 0; x < sizeX; ++x) {
            if(map[y][x] == '#' && countAdjoiningRoads(y, x) > 2){
                map[y][x] = 'x';
                crossroads.append(Coordinates(y, x));

            }

        }

    }

}
String& Navigator::findCityName(int cityY, int cityX){
    int nameY, nameX;
    for (int y = cityY-1; y <= cityY+1; ++y) {
        for (int x = cityX-1; x <=cityX+1; ++x) {
            if(coordsValid(y, x) && isLetterOrNumber(map[y][x])){
                nameY = y;
                nameX = x;
            }

        }

    }
    while(coordsValid(nameY, nameX-1) && isLetterOrNumber(map[nameY][nameX-1]))
        nameX -= 1;
    auto * name = new String();
    name->add(map[nameY][nameX]);
    while(coordsValid(nameY, nameX+1) && isLetterOrNumber(map[nameY][nameX+1])){
        name->add(map[nameY][++nameX]);

    }
    return *name;


}
void Navigator::findCities(){
    for (int y = 0; y < sizeY; ++y) {
        for (int x = 0; x < sizeX; ++x) {
            if(map[y][x] == '*'){
                String name = findCityName(y, x);
                cities.append(new City(name, y, x));

            }

        }

    }

}
Coordinates * Navigator::findUnvisitedAdjoiningRoad(int y, int x, bool ** visited){
    int coords[4][2] = {{y-1, x
                        }, {y+1, x
                        }, {y, x-1
                        }, {y, x+1
                        }
    };
    for(auto coord : coords){
        y = coord[0];
        x = coord[1];
        if(coordsValid(y, x) && !visited[y][x] && (map[y][x] == '#' || map[y][x] == 'x' || map[y][x] == '*'))
            return new Coordinates(y, x);

    }
    return nullptr;

}

void Navigator::findConnections(){
    bool ** visited = new bool * [sizeY];
    for (int y = 0; y < sizeY; ++y) {
        visited[y] = new bool[sizeX];
        for (int x = 0; x < sizeX; ++x) {
            switch (map[y][x]) {
                case '#':
                case 'x':
                case '*':
                    visited[y][x] = false;
                    break;
                default:
                    visited[y][x] = true;

            }

        }

    }
    for (int i = 0; i < cities.size(); ++i) {
        City * city = cities.get(i);
        findEdgesFromPoint(city->position.y, city->position.x, visited);

    }
    for (int i = 0; i < crossroads.size(); ++i) {
        Coordinates position = crossroads.get(i);
        findEdgesFromPoint(position.y, position.x, visited);

    }
    for (int i = 0; i < airConnections->size(); ++i) {
        Connection * connection = airConnections->get(i);
        City * departure = findCityByName(connection->departure);
        City * origin = findCityByName(connection->origin);
        if(departure != nullptr && origin != nullptr)
            edges.append(new Edge(departure->position, origin->position, connection->time, false));


    }

}
void Navigator::findEdgesFromPoint(int startY, int startX, bool ** visited){
    int y = startY;
    int x = startX;
    List<int*> endPoints = List<int*>();
    if(map[y][x] != '*' && map[y][x] != 'x')
        return;
    while(findUnvisitedAdjoiningRoad(startY, startX, visited) != nullptr){
        y = startY;
        x = startX;
        List<Coordinates> path = List<Coordinates>();
        path.append(Coordinates(y, x));
        visited[y][x] = true;
        while(findUnvisitedAdjoiningRoad(y, x, visited) != nullptr){
            Coordinates * position = findUnvisitedAdjoiningRoad(y, x, visited);
            y = position->y;
            x = position->x;
            visited[y][x] = true;
            path.append(*position);
            if(map[y][x] == '*' || map[y][x] == 'x')
                break;

        }
        Coordinates start = path.get(0);
        Coordinates end = path.get(path.size()-1);
        if(map[end.y][end.x] != '*' && map[end.y][end.x] != 'x')
            continue;
        visited[start.y][start.x] = false;
        int * endPoint = new int[2];
        endPoint[0] = end.y;
        endPoint[1] = end.x;
        endPoints.append(endPoint);
        edges.append(new Edge(start, end, path.size()-1, true));
        if(path.size()-1 == 0) printf("Sth..\n");

    }
    for (int i = 0; i < endPoints.size(); ++i) {
        y = endPoints.get(i)[0];
        x = endPoints.get(i)[1];
        visited[y][x] = false;

    }
    visited[startY][startX] = true;

}

City * Navigator::findCityByName(const String& name){
    for (int i = 0; i < cities.size(); ++i) {
        City * city = cities.get(i);
        if(city->name == name)
            return city;

    }
    return nullptr;

}

void Navigator::executeQueries(){
    for (int i = 0; i < queries->size(); ++i) {
        Query query = queries->get(i);
        String departure = query.departure;
        String origin = query.origin;
        if(findCityByName(origin) != nullptr && findCityByName(departure) != nullptr){
            int mode = query.mode;
            int start = navigationMap->getVertexIndex(findCityByName(departure)->position, navigationMap->nOfVertexes);
            int stop = navigationMap->getVertexIndex(findCityByName(origin)->position, navigationMap->nOfVertexes);
            if(start == stop)
                printf("0\n");
            else
                dijkstra(*navigationMap, start, stop, mode);

        }

    }

}

void Navigator::printCities(){
    for (int i = 0; i < cities.size(); ++i) {
        printf("%d.\t", i+1);
        cities.get(i)->print();
    }

}
void Navigator::printConnections(){
    printf("Air connections:\n");
    for (int i = 0; i < airConnections->size(); ++i) {
        printf("%d.\t", i+1);
        airConnections->get(i)->print();

    }
    printf("Land connections:\n");
    for (int i = 0; i < connections.size(); ++i) {
        connections.get(i)->print();

    }
    printf("---------------------------\n");

}
void Navigator::printQueries(){
    for (int i = 0; i < queries->size(); ++i) {
        printf("%d.\t", i+1);
        queries->get(i).print();

    }

}
void Navigator::printCrossroads(){
    for (int i = 0; i < crossroads.size(); ++i) {
        Coordinates position = crossroads.get(i);
        printf("%2d. - (%d, %d)\n", i+1, position.y, position.x);

    }

}
void Navigator::printMap(){
    for (int y = 0; y < sizeY; ++y) {
        printf("%d.\t", y+1);
        for (int x = 0; x < sizeX; ++x) {
            printf("%c", map[y][x]);

        }
        printf("\n");

    }

}
void Navigator::printEdges(){
    for (int i = 0; i < edges.size(); ++i) {
        edges.get(i)->print();
    }
}

void Navigator::printPath(int currentVertex, int * parents)
{
    if (parents[parents[currentVertex]] == -1) {
        return;
    }
    printPath(parents[currentVertex], parents);
    int y = navigationMap->coords[parents[currentVertex]][0];
    int x = navigationMap->coords[parents[currentVertex]][1];
    if(isCity(y, x)){
        String cityName = findCityName(y, x);
        cityName.print();
        printf(" ");
    }
}

void Navigator::printSolution(int startVertex,  int * distances, int * parents, int nVertices)
{
    printf("Vertex\t Distance\tPath\n");

    for (int vertexIndex = 0; vertexIndex < nVertices;
         vertexIndex++) {
        if (vertexIndex != startVertex) {
            int y1 = navigationMap->coords[startVertex][0];
            int x1 = navigationMap->coords[startVertex][1];
            int y2 = navigationMap->coords[vertexIndex][0];
            int x2 = navigationMap->coords[vertexIndex][1];
            printf("%d.(%d,%d) -> %d.(%d,%d)\t\t%d\t\t", startVertex, y1, x1, vertexIndex, y2, x2, distances[vertexIndex]);
            printPath(vertexIndex, parents);
            printf("\n");

        }

    }
}

void Navigator::calculateTime(int endVertex, int * distances, int * parents, int mode){
    printf("%d ", distances[endVertex]);
    if(mode == 1){
         printPath(endVertex, parents);

    }
    printf("\n");

}

void Navigator::dijkstra(Graph& graph, int startVertex, int endVertex, int mode)
{
    int nVertices = graph.nOfVertexes;
    int * shortestDistances = new  int[nVertices];
    bool * added = new bool[nVertices];

    for (int vertexIndex = 0; vertexIndex < nVertices;
         vertexIndex++) {
        shortestDistances[vertexIndex] = INT_MAX;
        added[vertexIndex] = false;

    }

    shortestDistances[startVertex] = 0;
    int * parents = new int[nVertices];
    parents[startVertex] = -1;
    for (int i = 1; i < nVertices; i++) {
        int nearestVertex = -1;
        int shortestDistance = INT_MAX;
        for (int vertexIndex = 0; vertexIndex < nVertices; vertexIndex++) {
            if (!added[vertexIndex] && shortestDistances[vertexIndex] < shortestDistance) {
                nearestVertex = vertexIndex;
                shortestDistance = shortestDistances[vertexIndex];
            }
        }
        added[nearestVertex] = true;
        for (int vertexIndex = 0; vertexIndex < nVertices;
             vertexIndex++) {
            int edgeDistance;
            if(vertexIndex != -1 && nearestVertex != -1){
                edgeDistance = graph.adjacencyMatrix[nearestVertex][vertexIndex];
            }
            else{
                edgeDistance = -1;
            }

            if (edgeDistance > 0 && ((shortestDistance + edgeDistance) < shortestDistances[vertexIndex])) {
                parents[vertexIndex] = nearestVertex;
                shortestDistances[vertexIndex] = shortestDistance + edgeDistance;
            }
        }
    }
    // printSolution(startVertex, shortestDistances, parents, nVertices);
    calculateTime(endVertex, shortestDistances, parents, mode);
}



void Navigator::optimizeMap(){
    int counter = 0;
    for (int y = 1; y < sizeY-1; ++y) {
        for (int x = 1; x < sizeX-1; ++x) {
            if(uselessTile(y, x)){
                map[y][x] = '.';
                counter += 1;
            }
        }
    }
    // printf("Optimized %d tiles\n", counter);
}

bool Navigator::uselessTile(int y, int x){
    if(coordsValid(y-1, x-1) && coordsValid(y+1, x+1) && coordsValid(y-1, x+1) && coordsValid(y+1, x-1)){
        for (int i = 0; i < 20; ++i) {
            if(type(map[y-1][x-1]) == uselessRoadsPatterns[i][0][0]
            && type(map[y-1][x]) == uselessRoadsPatterns[i][0][1]
               && type(map[y-1][x+1]) == uselessRoadsPatterns[i][0][2]
                  && type(map[y][x-1]) == uselessRoadsPatterns[i][1][0]
                     && map[y][x] == '#'
                        && type(map[y][x+1]) == uselessRoadsPatterns[i][1][2]
                           && type(map[y+1][x-1]) == uselessRoadsPatterns[i][2][0]
                              && type(map[y+1][x]) == uselessRoadsPatterns[i][2][1]
                                 && type(map[y+1][x+1]) == uselessRoadsPatterns[i][2][2])
                return true;
        }
    }
    return false;
}

bool Navigator::isCity(int y, int x){
    if(coordsValid(y, x)){
        for (int i = 0; i < cities.size(); ++i) {
            City * city = cities.get(i);
            if(city->position.y == y && city->position.x == x)
                return true;
        }
    }
    return false;
}


Navigator::~Navigator(){
    for (int i = sizeY-1; i >= 0; --i) {
        delete[] map[i];

    }
    delete[] map;
    delete airConnections;
    delete queries;
    delete navigationMap;

}


bool Navigator::isLetterOrNumber(char c){
    return (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}


char Navigator::type(char c){
    if(c == '#' || c == 'x' || c == '*')
        return 'r';
    else
        return 'c';
}