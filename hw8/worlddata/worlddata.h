//
// Created by furetur on 14.03.2020.
//

#ifndef HOMEWORK_WORLDDATA_H
#define HOMEWORK_WORLDDATA_H

#include "../../lib/graph/graph.h"
#include "../countrydata/countrydata.h"

struct WorldData
{
    GraphAdjacencyList* map;
    struct CountryData** countries;
    int countriesNum;
    int* cityOwnership;
};

typedef struct WorldData WorldData;

WorldData* newWorldData(GraphAdjacencyList* graph, const int* capitalsIds, int capitalsNum);

void deleteWorldData(WorldData* worldData);

bool isCityClaimed(const WorldData* worldData, int cityId);

void claimAllCities(WorldData* worldData);

LinkedList* getCitiesOf(const WorldData* worldData, int countryId);

#endif //HOMEWORK_WORLDDATA_H
