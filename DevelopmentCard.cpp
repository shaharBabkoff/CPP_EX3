#include "DevelopmentCard.hpp"
DevelopmentCard::~DevelopmentCard()
{
    // Empty implementation
}
bool DevelopmentCard::getIfIsUsed()
{
    return isUsed_;
}
void DevelopmentCard::activateFirstCheck(Player *player)
{
    if (!player->isPlayerTurn())
    {
        std::cerr << "not " << player->getPlayerName() << " turn..." << std::endl;
        return;
    }
    if (this->isUsed_)
    {
        std::cerr << "card was already in use..." << std::endl;
        return;
    }
    if (!player->hasRequiredResources({ResourceType::ORE, ResourceType::GRAIN, ResourceType::WOOL}))
    {
        std::cerr << "Player does not have the right resources" << std::endl;
        return;
    }
}
void DevelopmentCard::activateEnd(Player *player)
{
    player->addAndSubMultyResources({{ResourceType::ORE, -1}, {ResourceType::GRAIN, -1}, {ResourceType::WOOL, -1}});
    this->isUsed_ = true;
}
void RoadBuildingCard::activate(Player *player)
{
    activateFirstCheck(player);
    player->addAndSubMultyResources({{ResourceType::BRICK, 2}, {ResourceType::LUMBER, 2}});
}

void KnightCard ::activate(Player *player)
{
    activateFirstCheck(player);
    if (player->getKnightCardsNum() == 3)
    {
        std::cerr << "too much knight cards..." << std::endl;
        return;
    }
    player->addKnightCard();
    activateEnd(player);

    if (player->getKnightCardsNum() == 3)
    {
        player->addPoint(2);
    }
}

void VictoryCard ::activate(Player *player)
{
    activateFirstCheck(player);
    player->addPoint(1);
    activateEnd(player);
}
MonopolyCard::MonopolyCard(std::vector<Player *> playersList)
{
    playersList_ = playersList;
}
void MonopolyCard ::activate(Player *player)
{
    if (resource_ == ResourceType::NONE)
    {
        std::cerr << "you need first to set your source..." << std::endl;
        return;
    }

    activateFirstCheck(player);
    for (Player *p : playersList_)
    {

        int numOfResorce = p->getResorceCount(resource_);
        p->addAndSubResource(resource_, -numOfResorce);
        player->addAndSubResource(resource_, numOfResorce);
        activateEnd(player);
    }
}
void MonopolyCard::setResource(ResourceType resource)
{
    resource_ = resource;
}

void YearOfPlenty ::activate(Player *player)
{
    if (resource1_ == ResourceType::NONE || resource2_ == ResourceType::NONE)
    {
        std::cerr << "you need first to set your sources..." << std::endl;
        return;
    }
    activateFirstCheck(player);
    player->addAndSubResource(resource1_, 1);
    player->addAndSubResource(resource2_, 1);
    activateEnd(player);
}
void YearOfPlenty::setResources(ResourceType resource1, ResourceType resource2)
{
    resource1_ = resource1;
    resource2_ = resource2;
}

