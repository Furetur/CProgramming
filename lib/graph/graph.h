//
// Created by furetur on 13.03.2020.
//

#ifndef HOMEWORK_GRAPH_H
#define HOMEWORK_GRAPH_H

#include "../linkedlist/linkedlist.h"

typedef struct GraphAdjacencyList
{
    int numVertices;
    int numEdges;
    LinkedList** adjacencyList;
    LinkedList** edgesWeights;
} GraphAdjacencyList;


GraphAdjacencyList* newGraphAdjacencyList(int numVertices);

void deleteGraphAdjacencyList(GraphAdjacencyList* graph);

void graphAdjacencyListAddEdge(GraphAdjacencyList* graph, int startVertex, int endVertex, int weight);

int* findDistances(const GraphAdjacencyList* graph, int startVertex);

#endif //HOMEWORK_GRAPH_H
