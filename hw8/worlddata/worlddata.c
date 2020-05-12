//
// Created by furetur on 14.03.2020.
//


#include "../../lib/graph/graph.h"
#include "worlddata.h"
#include "stdlib.h"
#include "../../lib/arrayutils/arrayutils.h"


const int UNCLAIMED_CITY_COUNTRY_VALUE = -1;


WorldData* newWorldData(GraphAdjacencyList* graph, const int* capitalsIds, const int capitalsNum)
{
    WorldData* worldData = malloc(sizeof(WorldData));

    worldData->map = graph;
    worldData->cityOwnership = createIntArrayWithVal(graph->numVertices, UNCLAIMED_CITY_COUNTRY_VALUE);
    worldData->countries = calloc(capitalsNum, sizeof(CountryData));
    worldData->countriesNum = capitalsNum;

    for (int countryId = 0; countryId < capitalsNum; ++countryId)
    {
        const int currentCapitalId = capitalsIds[countryId];

        worldData->countries[countryId] = newCountryData(currentCapitalId, graph);
        worldData->cityOwnership[currentCapitalId] = countryId;
    }
    return worldData;
}

// does not delete the graph
void deleteWorldData(WorldData* worldData)
{
    for (int i = 0; i < worldData->countriesNum; ++i)
    {
        deleteCountryData(worldData->countries[i]);
    }
    free(worldData->countries);
    free(worldData->cityOwnership);
    free(worldData);
}

bool isCityClaimed(const WorldData* worldData, const int cityId)
{
    return worldData->cityOwnership[cityId] != UNCLAIMED_CITY_COUNTRY_VALUE;
}


void claimCity(WorldData* worldData, const int countryId, const int cityId)
{
    worldData->cityOwnership[cityId] = countryId;

    CountryData* country = worldData->countries[countryId];

    markCityClaimed(country, worldData->map, cityId);
}


int getNextCityOfInterest(const WorldData* worldData, const CountryData* countryData, const int citiesNum)
{
    int currentCityOfInterestIndex = 0;
    int currentCityOfInterestId = countryData->closestCityIds[currentCityOfInterestIndex];

    while (
        currentCityOfInterestIndex < citiesNum &&
        (!isCityReachable(countryData, currentCityOfInterestId) || isCityClaimed(worldData, currentCityOfInterestId))
    )
    {
        currentCityOfInterestIndex += 1;
        currentCityOfInterestId = countryData->closestCityIds[currentCityOfInterestIndex];
    }

    if (currentCityOfInterestIndex >= citiesNum)
    {
        return -1;
    }

    return currentCityOfInterestId;
}


void claimNextCity(WorldData* worldData, const int countryId)
{
    const int citiesNum = worldData->map->numVertices;
    const CountryData* countryData = worldData->countries[countryId];

    const int cityOfInterestId = getNextCityOfInterest(worldData, countryData, citiesNum);

    if (cityOfInterestId == -1)
    {
        return;
    }

    claimCity(worldData, countryId, cityOfInterestId);
}


bool areAllCitiesClaimed(WorldData* worldData)
{
    const int citiesNum = worldData->map->numVertices;

    for (int cityId = 0; cityId < citiesNum; ++cityId)
    {
        if (!isCityClaimed(worldData, cityId))
        {
            return false;
        }
    }
    return true;
}


void claimAllCities(WorldData* worldData)
{
    const int countriesNum = worldData->countriesNum;
    int curCountryId = 0;

    while(!areAllCitiesClaimed(worldData))
    {
        claimNextCity(worldData, curCountryId);

        curCountryId = (curCountryId + 1) % countriesNum;
    }
}


LinkedList* getCitiesOf(const WorldData* worldData, const int countryId)
{
    const int citiesNum = worldData->map->numVertices;

    LinkedList* citiesIds = newLinkedList();

    for (int cityId = 0; cityId < citiesNum; ++cityId)
    {
        if (worldData->cityOwnership[cityId] == countryId)
        {
            linkedListPushBack(citiesIds, cityId);
        }
    }

    return citiesIds;
}