#ifndef CATAN_HPP
#define CATAN_HPP

  // Included here because Catan.cpp will likely need complete types
#include "Player.hpp"
#include "Board.hpp"
//class Board;

class Catan
{
private:
    Board* board_;
    std::vector<Player *> playersList_;
    int currentPlayerIndex_ = 1;

public:
    Catan(Player *p1, Player *p2, Player *p3)
    {
        playersList_.push_back(p1);
        playersList_.push_back(p2);
        playersList_.push_back(p3);
        board_ = new Board();
    }
    ~Catan(){}

    void ChooseStartingPlayer();
    Board *getBoard();
    std::vector<Player *> getPlayersList()
    {
        return playersList_;
    }
    int getCurrentPlayerIndex(){
        return currentPlayerIndex_;
    }
    void setCurrentIndex(int index){
        currentPlayerIndex_=index;
    }
    void printWinner();
    void printPlayersStatus();
    void endTurn();
};

#endif // CATAN_HPP
