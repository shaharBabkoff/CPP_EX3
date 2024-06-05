#ifndef CATAN_HPP
#define CATAN_HPP
#include <memory>
#include <unordered_map>
#include <string>
#include "Player.hpp"
#include "Board.hpp"
#include "DevelopmentCard.hpp"
// class Board;
#include <unordered_map>
#include <string>

enum CardType
{
    KNIGHT,
    VICTORY,
    MONOPOLY,
    YEAR_OF_PLENTY,
    ROADS,
    UNKNOWN
};

class Catan
{
private:
    Board *board_;
    std::vector<Player *> playersList_;
    int currentPlayerIndex_ = 1;
    std::vector<DevelopmentCard *> developmentCards_;

public:
    Catan(Player *p1, Player *p2, Player *p3);
    ~Catan();
    void ChooseStartingPlayer();
    Board *getBoard();
    std::vector<Player *> getPlayersList();
    int getCurrentPlayerIndex();
    DevelopmentCard *getDevelopmentCard(CardType type);
    void setCurrentIndex(int index);
    void printWinner();
    void printPlayersStatus();
    void endTurn();
    void initialDevelopmentCards();
};

#endif // CATAN_HPP
