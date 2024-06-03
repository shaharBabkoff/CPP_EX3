#include "Catan.hpp"
#include <iostream>
using namespace std;

void Catan::ChooseStartingPlayer()
{
    currentPlayerIndex_ = 1;
    std::cout << "Choosing starting player..." << std::endl;
    playersList_[0]->setPlayerTurn(true);
    std::cout << playersList_[0]->getPlayerName() << " is the starting player." << std::endl;
}
Board& Catan::getBoard()
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
void Catan::printPlayersStatus(){
    for(Player* p : playersList_){
        cout<<p->getPlayerName()<<" has:"<<endl<<p->getPlayerEdgesList().size()<<" roads"<<endl;
        cout<<p->getPlayerVerticesList().size()<<" settelments"<<endl;
        cout<<"brick: "<<p->getResorceCount(ResourceType::BRICK)<<endl;
        cout<<"ore: "<<p->getResorceCount(ResourceType::ORE)<<endl;
        cout<<"lumber: "<<p->getResorceCount(ResourceType::LUMBER)<<endl;
        cout<<"grain: "<<p->getResorceCount(ResourceType::GRAIN)<<endl;
        cout<<"wool: "<<p->getResorceCount(ResourceType::WOOL)<<endl;
    }
}