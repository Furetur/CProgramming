//
// Created by furetur on 14.03.2020.
//

#ifndef HOMEWORK_COUNTRYDATA_H
#define HOMEWORK_COUNTRYDATA_H

#include <stdbool.h>
#include "../../lib/graph/graph.h"
#include "../worlddata/worlddata.h"


struct CountryData
{
    int capitalId;
    int* closestCityIds;
    bool* reachableCities;
    int lastCityInInterest;
};

typedef struct CountryData CountryData;

CountryData* newCountryData(int capitalId, GraphAdjacencyList* graph);

void deleteCountryData(CountryData* countryData);

bool isCityReachable(const CountryData* countryData, int cityId);

void markCityClaimed(CountryData* countryData, GraphAdjacencyList* graph, int cityId);


#endif //HOMEWORK_COUNTRYDATA_H
