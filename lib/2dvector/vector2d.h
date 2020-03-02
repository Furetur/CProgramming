//
// Created by furetur on 29.02.2020.
//

#ifndef HOMEWORK_VECTOR2D_H
#define HOMEWORK_VECTOR2D_H

typedef struct Vector {
    int x, y;
} Vector2d;


Vector2d vectorSum(Vector2d* vector1, Vector2d* vector2);

Vector2d vectorTurnClockwise(Vector2d* vector);


#endif //HOMEWORK_VECTOR2D_H
