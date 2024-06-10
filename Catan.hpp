//id:324207935 email:shbabkoff123@gmail.coms
#ifndef CATAN_HPP
#define CATAN_HPP
#include <memory>
#include <unordered_map>
#include <string>
#include "Player.hpp"
#include "Board.hpp"
#include "DevelopmentCard.hpp"
#include "CardType.hpp"
#include <unordered_map>
#include <string>



class Catan
{
private:
    Board board_;
    std::vector<Player *> playersList_;
    int currentPlayerIndex_ = 1;
    std::vector<DevelopmentCard *> developmentCards_;

public:
    Catan(Player *p1, Player *p2, Player *p3);
    ~Catan();
     Board&  getBoard();
    std::vector<Player *> getPlayersList() const;
    int getCurrentPlayerIndex() const;
    DevelopmentCard* getDevelopmentCard(CardType type, Player &player) const;
    void setCurrentIndex(int index);
    std::string printWinner();
    void printPlayersStatus();
    void endTurn();
    void initialDevelopmentCards();
    
};

#endif // CATAN_HPP
