#ifndef TTT_HPP
#define TTT_HPP

#include <vector>
#include <tuple>


enum class Player {
    None,
    X,
    O
};


class TicTacToe {
private:
    std::vector<std::vector<Player>> board;
    Player currentPlayer;
    int remainingMoves;

    void show_board() const;
    std::tuple<int, int> take_player_input() const;
    bool check_winner(int row_idx, int col_idx) const;

public:
    TicTacToe();
    void play();
};

#endif