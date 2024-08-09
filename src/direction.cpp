#include "direction.hpp"

std::pair<int, int> steps_from_direction(Direction direction) {
    std::pair<int, int> steps;
    switch (direction) {
        case Vertical:
            // Col = 0, Row = +1 (Up)
            steps = std::make_pair(0, 1);
            break;
        case Horizontal:
            // Col = +1, Row = 0 (Right)
            steps = std::make_pair(1, 0);
            break;
        case L_Diagonal:
            // Col = -1, Row = +1 (Up-Left)
            steps = std::make_pair(-1, 1);
            break;
        case R_Diagonal:
            // Col = +1, Row = +1 (Up-Right)
            steps = std::make_pair(1, 1);
            break;
    }
    return steps;
}