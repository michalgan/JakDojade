//
// Created by micha on 4/28/2023.
//

#ifndef JAKDOJADE_GRAPH_H
#define JAKDOJADE_GRAPH_H


#include "Edge.h"
#include "List.h"
#include "Vertex.h"


struct Edge;
struct Vertex;
struct Graph {
    Graph(int n, List<Edge*> &edges): nOfVertexes(n){
        adjacencyMatrix = new int * [nOfVertexes];
        for (int y = 0; y < nOfVertexes; ++y) {
            adjacencyMatrix[y] = new int[nOfVertexes];
            for (int x = 0; x < nOfVertexes; ++x) {
                adjacencyMatrix[y][x] = 0;

            }

        }
        int counter = 0;
        coords = new int * [nOfVertexes];
        for (int i = 0; i < nOfVertexes; ++i) {
            coords[i] = new int[2];

        }
        for (int i = 0; i < edges.size(); ++i) {
            Edge* edge = edges.get(i);
            int index1 = getVertexIndex(edge->start, counter);
            if(index1 == -1){
                index1 = counter;
                coords[counter][0] = edge->start.y;
                coords[counter++][1] = edge->start.x;

            }
            int index2 = getVertexIndex(edge->end, counter);
            if(index2 == -1){
                index2 = counter;
                coords[counter][0] = edge->end.y;
                coords[counter++][1] = edge->end.x;
            }
            if(adjacencyMatrix[index2][index1] == 0 || adjacencyMatrix[index2][index1] > edge->wage){
                if(edge->bothDirections)
                    adjacencyMatrix[index1][index2] = edge->wage;
                adjacencyMatrix[index2][index1] = edge->wage;
            }

        }

    }
    int getVertexIndex(Coordinates position, int counter) const{
        for (int i = 0; i < counter; ++i) {
            if(position.y == coords[i][0] && position.x == coords[i][1])
                return i;

        }
        return -1;

    }
    void printMatrix() const{
        int counter = 0;
        printf("   ");
        for (int i = 1; i <= nOfVertexes; ++i) {
            printf("%3d", i);

        }
        printf("\n");
        for (int y = 0; y < nOfVertexes; ++y) {
            printf("%2d.", y+1);
            for (int x = 0; x < nOfVertexes; ++x) {
                if(adjacencyMatrix[y][x])
                    printf("%3d", adjacencyMatrix[y][x]);
                else
                    printf("   ");
                if(adjacencyMatrix[y][x] > 0)
                    counter += 1;

            }
            printf("\n");

        }
        printf("Edges: %d\n\n\n", counter/2);

    }

    ~Graph(){
        delete[] adjacencyMatrix;
        delete[] coords;

    }
    int ** adjacencyMatrix;
    int ** coords;
    int nOfVertexes;
};


#endif //JAKDOJADE_GRAPH_H