#ifndef BOARD_H
#define BOARD_H
#include <array>
#include <vector>
#include <utility>
#include "connection.hpp"

#define COLUMNS 7
#define ROWS 6

#define PLAYER_T 'o'
#define COMPUTER_T 'x'
#define EMPTY_T '-'

class Board {
        std::array<std::array<char, ROWS>, COLUMNS> layout;
        bool player_playing;
    public:
        Board();
        bool in_bounds(int column, int row);
        int get_highest_empty_space(int column);
        int evaluate_actual_position(int column, int row);
        int evaluate_potential_position(int column, int row, char token);
        std::vector<std::pair<int, int>> get_legal_moves(); 
        bool is_player_playing() {
            return player_playing;
        };
        bool place_token(int column, bool player);
        Connection connections(int column, int row, char token, Direction direction);
        
        // DEBUGGING
        void print_board();
};

#endif