#ifndef DIRECTION_H
#define DIRECTION_H

#include <utility>

enum Direction { Vertical, Horizontal, L_Diagonal, R_Diagonal };

std::pair<int, int> steps_from_direction(Direction direction);

#endif