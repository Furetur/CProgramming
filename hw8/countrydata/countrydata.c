//
// Created by furetur on 14.03.2020.
//

#include <stdbool.h>
#include "countrydata.h"
#include "../../lib/graph/graph.h"
#include "../../lib/pair/pair.h"
#include "../../lib/arrayutils/arrayutils.h"
#include "stdlib.h"
#include "../worlddata/worlddata.h"


int* getClosestCityIdsForCapital(const GraphAdjacencyList* graph, const int capitalId)
{
    int* distances = findDistances(graph, capitalId);
    int* result = sortIndexesByValues(distances, graph->numVertices);

    free(distances);
    return result;
}


void markCitiesReachable(GraphAdjacencyList* graph, int keyCityId, bool* reachableCities)
{
    reachableCities[keyCityId] = true;

    LinkedList* neighbours = graph->adjacencyList[keyCityId];
    LinkedListIterator* neighboursIterator = getLinkedListIterator(neighbours);

    while(linkedListIteratorHasNext(neighboursIterator))
    {
        const int curNeighbour = linkedListIteratorGetNext(neighboursIterator);
        // mark neighbour visited
        reachableCities[curNeighbour] = true;
    }
    free(neighboursIterator);
}


CountryData* newCountryData(const int capitalId, GraphAdjacencyList* graph)
{
    CountryData* countryData = malloc(sizeof(CountryData));

    countryData->capitalId = capitalId;
    countryData->closestCityIds = getClosestCityIdsForCapital(graph, capitalId);
    countryData->reachableCities = createBoolArray(graph->numVertices);
    countryData->lastCityInInterest = -1;
    markCitiesReachable(graph, capitalId, countryData->reachableCities);

    return countryData;
}


void deleteCountryData(CountryData* countryData)
{
    free(countryData->closestCityIds);
    free(countryData->reachableCities);
    free(countryData);
}


bool isCityReachable(const CountryData* countryData, const int cityId)
{
    return countryData->reachableCities[cityId];
}


void markCityClaimed(CountryData* countryData, GraphAdjacencyList* graph, const int cityId)
{
    markCitiesReachable(graph, cityId, countryData->reachableCities);
}
