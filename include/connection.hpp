#ifndef CONNECTION_H
#define CONNECTION_H

#include <vector>
#include <utility>
#include "direction.hpp"

class Connection {
    public:
        Connection(std::pair<int, int> origin, Direction direction);
        // Origin of connection calculation.
        std::pair<int, int> origin;
        // Direction of connection.
        Direction direction;
        // Vector of Column/Row pairs.
        std::vector<std::pair<int, int>> members;

        int length();
        void add_member(std::pair<int, int> cell);
        void add_member(int column, int row);
        bool has_member(int column, int row);
};

#endif