//
// Created by furetur on 29.02.2020.
//

#include "vector2d.h"


Vector2d vectorSum(Vector2d* vector1, Vector2d* vector2)
{
    return (Vector2d) {.x = vector1->x + vector2->x,
                     .y = vector1->y + vector2->y};
}


Vector2d vectorTurnClockwise(Vector2d* vector)
{
    return (Vector2d) {.x = vector->y, .y = -1 * vector->x};
}




