#include <vector>
#include <algorithm>
#include <utility>
#include "connection.hpp"

Connection::Connection(std::pair<int, int> origin, Direction direction) {
    this->origin = origin;
    this->add_member(origin);
    this->direction = direction;
}

int Connection::length() {
    return this->members.size();
}

void Connection::add_member(std::pair<int, int> cell) {
    if (!this->has_member(cell.first, cell.second)) {
        this->members.push_back(cell);
    }    
}

void Connection::add_member(int column, int row) {
    if (!this->has_member(column, row)) {
        this->members.push_back(std::make_pair(column, row));
    }
}

bool Connection::has_member(int column, int row) {
    for (auto const& pair : this->members) {
        if (pair.first == column && pair.second == row) {
            return true;
        }
    }
    return false;
}