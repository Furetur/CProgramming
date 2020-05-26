//
// Created by furetur on 13.03.2020.
//

#include "../lib/graph/graph.h"
#include "stdio.h"
#include "../lib/arrayutils/arrayutils.h"
#include "../lib/pair/pair.h"
#include "stdlib.h"
#include "worlddata/worlddata.h"
#include "../lib/commonutils/commonutils.h"


GraphAdjacencyList* readCitiesGraph()
{
    int citiesNum = 0;
    int roadsNum = 0;
    printf("Enter the number of cities\n");
    scanf("%d", &citiesNum);
    printf("Enter the number of roads\n");
    scanf("%d", &roadsNum);

    GraphAdjacencyList* citiesGraph = newGraphAdjacencyList(citiesNum);

    printf("Enter the roads. Each road is a tuple: <start city> <destination city> <length>\n");
    for (int i = 0; i < roadsNum; ++i)
    {
        int roadStartCity = 0;
        int roadEndCity = 0;
        int roadLength = 0;
        scanf("%d", &roadStartCity);
        scanf("%d", &roadEndCity);
        scanf("%d", &roadLength);

        graphAdjacencyListAddEdge(citiesGraph, roadStartCity - 1, roadEndCity - 1, roadLength);
        graphAdjacencyListAddEdge(citiesGraph, roadEndCity - 1, roadStartCity - 1, roadLength);
    }
    return citiesGraph;
}


int* readCapitals(int* capitalsNum)
{
    printf("Enter the number of capitals\n");
    scanf("%d", capitalsNum);

    int* capitalIds = createIntArray(*capitalsNum);

    printf("Enter the capitals\n");
    for (int countryId = 0; countryId < *capitalsNum; ++countryId)
    {
        int curCapitalId = 0;
        scanf("%d", &curCapitalId);
        capitalIds[countryId] = curCapitalId - 1;
    }

    return capitalIds;
}


void printCitiesOfCountries(WorldData* worldData)
{
    const int capitalsNum = worldData->countriesNum;

    for (int countryId = 0; countryId < capitalsNum; ++countryId)
    {
        LinkedList* countryCities = getCitiesOf(worldData, countryId);
        LinkedListIterator* countryCitiesIterator = getLinkedListIterator(countryCities);

        printf("Cities of country %d \n", countryId + 1);

        while(linkedListIteratorHasNext(countryCitiesIterator))
        {
            printf("%d ", linkedListIteratorGetNext(countryCitiesIterator) + 1);
        }
        printf("\n");

        deleteLinkedListIterator(countryCitiesIterator);
        deleteLinkedList(countryCities);
    }
}


int main()
{
    GraphAdjacencyList* citiesGraph = readCitiesGraph();

    int capitalsNum = 0;

    int* capitalIds = readCapitals(&capitalsNum);

    WorldData* worldData = newWorldData(citiesGraph, capitalIds, capitalsNum);

    claimAllCities(worldData);

    printCitiesOfCountries(worldData);

    free(capitalIds);
    deleteWorldData(worldData);
    deleteGraphAdjacencyList(citiesGraph);

    return 0;
}