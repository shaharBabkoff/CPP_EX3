#include "Catan.hpp"

#include <iostream>
using namespace std;
Catan::Catan(Player *p1, Player *p2, Player *p3)
{
    playersList_.push_back(p1);
    playersList_.push_back(p2);
    playersList_.push_back(p3);
    board_ = new Board();
    initialDevelopmentCards();
}
Catan::~Catan() {}
vector<Player *> Catan::getPlayersList()
{
    return playersList_;
}
int Catan::getCurrentPlayerIndex()
{
    return currentPlayerIndex_;
}
void Catan::setCurrentIndex(int index)
{
    currentPlayerIndex_ = index;
}
void Catan::ChooseStartingPlayer()
{
    currentPlayerIndex_ = 1;
    std::cout << "Choosing starting player..." << std::endl;
    playersList_[0]->setPlayerTurn(true);
    std::cout << playersList_[0]->getPlayerName() << " is the starting player." << std::endl;
}
Board *Catan::getBoard()
{
    return board_;
}
void Catan::printWinner()
{
    for (Player *p : playersList_)
    {
        if (p->getPlayerPoints() == 10)
        {
            cout << p->getPlayerName() << " win the game" << endl;
            return;
        }
    }
    cout << "no playaer has 10 points..." << endl;
}
void Catan::printPlayersStatus()
{
    for (Player *p : playersList_)
    {
        cout << p->getPlayerName() << " has:" << endl
             << p->getPlayerEdgesList().size() << " roads" << endl;
        cout << p->getPlayerVerticesList().size() << " settelments" << endl;
        cout << "brick: " << p->getResorceCount(ResourceType::BRICK) << endl;
        cout << "ore: " << p->getResorceCount(ResourceType::ORE) << endl;
        cout << "lumber: " << p->getResorceCount(ResourceType::LUMBER) << endl;
        cout << "grain: " << p->getResorceCount(ResourceType::GRAIN) << endl;
        cout << "wool: " << p->getResorceCount(ResourceType::WOOL) << endl;
    }
}
void Catan::endTurn()
{
    // int currentIndex = currentPlayerIndex_;
    int nextIndex = (currentPlayerIndex_ % 3) + 1; // Cycle through 1, 2, 3
    currentPlayerIndex_ = nextIndex;
    // catan->setCurrentIndex(nextIndex);

    for (int i = 0; i < 3; ++i)
    {
        playersList_[i]->setPlayerTurn(i + 1 == nextIndex);
    }
    
}
void Catan::initialDevelopmentCards()
{
    for (int i = 0; i < 3; i++)
    {
        developmentCards_.push_back(new KnightCard());
    }
    for (int i = 0; i < 4; i++)
    {
        developmentCards_.push_back(new VictoryCard());
    }
    for (int i = 0; i < 4; i++)
    {

        developmentCards_.push_back(new YearOfPlenty());
    }
    for (int i = 0; i < 4; i++)
    {

        developmentCards_.push_back(new MonopolyCard(playersList_));
    }
    for (int i = 0; i < 4; i++)
    {

        developmentCards_.push_back(new RoadBuildingCard());
    }
}
  DevelopmentCard* Catan:: getDevelopmentCard(CardType type) {
    int startIndex = 0, endIndex = 0;

     switch (type) {
        case KNIGHT:
            startIndex = 0;
            endIndex = 3;  // Exclusive, so actual last index is 2
            break;
        case VICTORY:
            startIndex = 3;
            endIndex = 7;  // Exclusive, so actual last index is 6
            break;
        case YEAR_OF_PLENTY:
            startIndex = 7;
            endIndex = 11;  // Exclusive, so actual last index is 10
            break;
        case MONOPOLY:
            startIndex = 11;
            endIndex = 15;  // Exclusive, so actual last index is 14
            break;
        case ROADS:
            startIndex = 15;
            endIndex = 19;  // Exclusive, so actual last index is 18
            break;
        default:
            return nullptr;  // Return null if card type is unknown or not handled
    }


    for (int i = startIndex; i < endIndex; i++) {
        if (!developmentCards_[i]->getIfIsUsed()) {
            return developmentCards_[i];
        }
    }
    std::cout<<"no valid card from your type"<<std::endl;
    return nullptr;  // Return null if all cards of the requested type are used
}
// std::cout << name_ << " ends his turn." << std::endl;
// // std::cout << "Current player index is now: " << catan.getCurrentPlayerIndex() << std::endl;
// for (int i = 0; i < 3; ++i)
// {
//     //  std::cout << "Player " << (i + 1) << " turn status: " << catan.getPlayersList()[i]->isPlayerTurn() << std::endl;
// }
