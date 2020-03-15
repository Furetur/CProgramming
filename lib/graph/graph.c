//
// Created by furetur on 13.03.2020.
//


#include <limits.h>
#include "graph.h"
#include "stdlib.h"
#include "../arrayutils/arrayutils.h"


const int DEFAULT_UNREACHED_DISTANCE = INT_MAX;

GraphAdjacencyList* newGraphAdjacencyList(const int numVertices)
{
    GraphAdjacencyList* graphAdjacencyList = malloc(sizeof(GraphAdjacencyList));
    graphAdjacencyList->numVertices = numVertices;
    graphAdjacencyList->numEdges = 0;

    LinkedList** adjacencyList = calloc(numVertices, sizeof(LinkedList*));
    LinkedList** edgesWeights = calloc(numVertices, sizeof(LinkedList*));

    for (int i = 0; i < numVertices; ++i)
    {
        adjacencyList[i] = newLinkedList();
        edgesWeights[i] = newLinkedList();
    }

    graphAdjacencyList->adjacencyList = adjacencyList;
    graphAdjacencyList->edgesWeights = edgesWeights;
    return graphAdjacencyList;
}

void deleteGraphAdjacencyList(GraphAdjacencyList* graph)
{
    for (int i = 0; i < graph->numVertices; ++i)
    {
        deleteLinkedList(graph->adjacencyList[i]);
        deleteLinkedList(graph->edgesWeights[i]);
    }
    free(graph->adjacencyList);
    free(graph->edgesWeights);
    free(graph);
}


void graphAdjacencyListAddEdge(GraphAdjacencyList* graph, int startVertex, int endVertex, int weight)
{
    linkedListPushBack(graph->adjacencyList[startVertex], endVertex);
    linkedListPushBack(graph->edgesWeights[startVertex], weight);
    graph->numEdges += 1;
}


int* findDistances(const GraphAdjacencyList* graph, const int startVertex)
{
    int* distances = createIntArrayWithVal(graph->numVertices, DEFAULT_UNREACHED_DISTANCE);

    distances[startVertex] = 0;

    bool* visited = createBoolArrayWithVal(graph->numVertices, false);

    int currentVertex = startVertex;

    // while there are unvisited vertices
    while (!allTruthy(visited, graph->numVertices))
    {
        // if the vertex is unreached
        if (distances[currentVertex] == DEFAULT_UNREACHED_DISTANCE)
        {
            visited[currentVertex] = true;
            currentVertex = findFirstInBoolArray(visited, false, graph->numVertices);
            continue;
        }

        LinkedList* currentVertexNeighbours = graph->adjacencyList[currentVertex];
        LinkedList* currentVertexEdgesWeights = graph->edgesWeights[currentVertex];

        LinkedListIterator* neighboursIterator = getLinkedListIterator(currentVertexNeighbours);
        LinkedListIterator* edgeWeightsIterator = getLinkedListIterator(currentVertexEdgesWeights);
        // iterate over neighbours
        while(linkedListIteratorHasNext(neighboursIterator))
        {
            int curNeighbour = linkedListIteratorGetNext(neighboursIterator);
            int curEdgeWeigth = linkedListIteratorGetNext(edgeWeightsIterator);
            // if the neighbour is visited than we skip it
            if (visited[curNeighbour])
            {
                continue;
            }
            const int newDistance = distances[currentVertex] + curEdgeWeigth;
            if (distances[curNeighbour] == DEFAULT_UNREACHED_DISTANCE || distances[curNeighbour] > newDistance)
            {
                distances[curNeighbour] = newDistance;
            }
        }

        visited[currentVertex] = true;
        currentVertex = findFirstInBoolArray(visited, false, graph->numVertices);

        deleteLinkedListIterator(neighboursIterator);
        deleteLinkedListIterator(edgeWeightsIterator);
    }

    free(visited);

    return distances;
}