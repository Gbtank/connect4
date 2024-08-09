#include <iostream>
#include "board.hpp"


Board::Board() {
    for (int col = 0; col < COLUMNS; ++col) {
        for (int row = 0; row < ROWS; ++row) {
            this->layout[col][row] = '-';
        }
    }
    this->player_playing = true;
}

bool Board::in_bounds(int column, int row) {
    if (column < 0 || column > COLUMNS - 1) {
        return false;
    }
    if (row < 0 || row > ROWS-1) {
        return false;
    }
    return true;
}

int Board::get_highest_empty_space(int column) {
    if (!this->in_bounds(column, 0)) {
        return -1;
    }
    int result = -1;
    for (int row = ROWS-1; row >= 0; --row) {
        char space = this->layout[column][row];
        if (space != '-') break;
        result = row;
    }
    return result;    
}

// Evaluates actual position on board.
int Board::evaluate_actual_position(int column, int row) {
    char token = this->layout[column][row];
    if (token == '-') {
        return 0;
    } else {
        return evaluate_potential_position(column, row, token);
    }
}

// Evaluates potential position of the board,
// if a token were to be placed in that position.
// Scores:
// 1 length = 1 point
// 2 length = 10 points
// 3 length = 100 points
// 4 length = 1_000_000 points (WIN CONDITION)
int Board::evaluate_potential_position(int column, int row, char token) {
    int eval = 0;
    for (int dir = Direction::Vertical; dir <= Direction::R_Diagonal; ++dir) {
        Direction direction = static_cast<Direction>(dir);
        Connection connection = this->connections(column, row, token, direction);
        switch (connection.length()) {
            case 0:
                eval += 0;
                break;
            case 1:
                eval += 1;
                break;
            case 2:
                eval += 10;
                break;
            case 3:
                eval += 100;
                break;
            default:
                eval += 1000000;
                break;
        }
    }
    return eval;
}

std::vector<std::pair<int, int>> Board::get_legal_moves() {
    std::vector<std::pair<int, int>> result;
    for (int col = 0; col < COLUMNS; ++col) {
        int row = this->get_highest_empty_space(col);
        if (row != -1) {
            result.push_back(std::make_pair(col, row));
        }
    }
    return result;
}

// Function to place a token in the a boards column.
// Returns false if not a legal move, 
// returns true and modifies board if it is a legal move.
bool Board::place_token(int column, bool player) {
    char token = player ? 'o' : 'x';
    int row = this->get_highest_empty_space(column);
    if (row == -1) {
        return false;
    }
    this->layout[column][row] = token;
    return true;
}

void Board::print_board() {
    std::cout << "--- START ---" << std::endl;
    // Start by printing top row first:
    // i.e. [0, ROWS-1], [1, ROWS-1], ... [COLS-1, ROWS-1]
    for (int row = ROWS-1; row >= 0; --row) {
        for (int col = 0; col < COLUMNS; ++col) {
            // DEBUG PRINT:
            // std::cout << "[" << col << ", " << row << "]" << ", ";
            std::cout << this->layout[col][row] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "--- FINISH ---" << std::endl;
}

// Returns the number of connections IF a token were to be placed in
// the given spot. This means it disregards whatever is in that location.
Connection Board::connections(int column, int row, char token, Direction direction) {
    Connection result(std::make_pair(column, row), direction);
    std::pair<int, int> steps = steps_from_direction(direction);
    int stepCol = steps.first;
    int stepRow = steps.second;

    // Go in positive direction
    int nextCol = column + stepCol;
    int nextRow = row + stepRow;
    while (this->in_bounds(nextCol, nextRow) && this->layout[nextCol][nextRow] == token) {
        result.add_member(nextCol, nextRow);
        nextCol += stepCol;
        nextRow += stepRow;
    }

    // Go in negative direction
    nextCol = column - stepCol;
    nextRow = row - stepRow;
    while (this->in_bounds(nextCol, nextRow) && this->layout[nextCol][nextRow] == token) {
        result.add_member(nextCol, nextRow);
        nextCol -= stepCol;
        nextRow -= stepRow;
    }
    return result;
}