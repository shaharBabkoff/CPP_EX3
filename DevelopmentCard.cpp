#include "DevelopmentCard.hpp"
using namespace std;

DevelopmentCard::~DevelopmentCard()
{
    // Empty implementation
}
bool DevelopmentCard::getIfBought() const
{
    return isBought_;
}
void DevelopmentCard::setAsBought(bool val)
{
    isBought_ = val;
}
void DevelopmentCard::activateFirstCheck(Player *player)
{
    if (!player->isPlayerTurn())
    {

        throw invalid_argument("not player turn");
    }
    if (this->isBought_ == false)
    {

        throw invalid_argument("card need to be bought first");
    }

    // All checks passed
}
void DevelopmentCard::activateEnd(Player *player)
{
    
    this->isBought_ = true;
    cout << "activate ended succesfully!" << endl;
}
void RoadBuildingCard::activate(Player *player)
{

    activateFirstCheck(player);
    player->addAndSubMultyResources({{ResourceType::BRICK, 2}, {ResourceType::LUMBER, 2}});
    player->addAndRemoveCard(CardType::ROADS, -1);
    activateEnd(player);
}

// void KnightCard ::activate(Player *player)
// {

//     if (!player->isPlayerTurn())
//     {

//         throw invalid_argument("not player turn");
//     }
//     if (this->isBought_ == false)
//     {

//         throw invalid_argument("card need to be bought first");
//     }
//     player->addKnightCard();

//     if (player->getKnightCardsNum() == 3)
//     {
//         player->addPoint(2);
//     }
//     player->addAndSubMultyResources({{ResourceType::ORE, -1}, {ResourceType::GRAIN, -1}, {ResourceType::WOOL, -1}});
//     this->isBought_ = true;
//     cout << "activate ended succesfully!" << endl;
// }

void VictoryCard ::activate(Player *player)
{
    activateFirstCheck(player);
    player->addPoint(1);
    player->addAndRemoveCard(CardType::VICTORY, -1);
    activateEnd(player);
}
MonopolyCard::MonopolyCard(vector<Player *> playersList)
{
    playersList_ = playersList;
}
void MonopolyCard ::activate(Player *player)
{
    if (resource_ == ResourceType::NONE)
    {
        throw invalid_argument("you need first to set your source");
    }

    activateFirstCheck(player);
    for (Player *p : playersList_)
    {
        if (p != player)
        {
            int numOfResorce = p->getResorceCount(resource_);
            if (numOfResorce > 0)
            {
                p->addAndSubResource(resource_, -numOfResorce);
                player->addAndSubResource(resource_, numOfResorce);
            }
        }
    }
    player->addAndRemoveCard(CardType::MONOPOLY, -1);
    activateEnd(player);
}
void MonopolyCard::setResource(ResourceType resource)
{
    resource_ = resource;
}

void YearOfPlenty ::activate(Player *player)
{
    if (resource1_ == ResourceType::NONE || resource2_ == ResourceType::NONE)
    {
        throw invalid_argument("you need first to set your resources");
    }

    activateFirstCheck(player);
    player->addAndSubResource(resource1_, 1);
    player->addAndSubResource(resource2_, 1);
    player->addAndRemoveCard(CardType::YEAR_OF_PLENTY, -1);
    activateEnd(player);
}
void YearOfPlenty::setResources(ResourceType resource1, ResourceType resource2)
{
    resource1_ = resource1;
    resource2_ = resource2;
}
