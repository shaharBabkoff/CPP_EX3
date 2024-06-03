#include "DevelopmentCard.hpp"
DevelopmentCard::~DevelopmentCard()
{
    // Empty implementation
}
void RoadBuildingCard::activate(Player *player)
{
    if (!player->hasRequiredResources({ResourceType::ORE, ResourceType::GRAIN, ResourceType::WOOL}))
    {
        std::cerr << "Player does not have the right resources" << std::endl;
        return;
    }
    player->addAndSubResource(ResourceType::BRICK, 2);
    player->addAndSubResource(ResourceType::LUMBER, 2);
    player->placeRoad({resourseTypes_[0], resourseTypes_[1]}, {itemNum_[0], itemNum_[1]}, board_);
    player->placeRoad({resourseTypes_[2], resourseTypes_[3]}, {itemNum_[2], itemNum_[3]}, board_);
    player->deductResources({{ResourceType::ORE, 1}, {ResourceType::GRAIN, 1}, {ResourceType::WOOL, 1}});
}
void RoadBuildingCard::set2roads(std::vector<ResourceType> resourseTypes, std::vector<int> itemNum, Board &board)
{
    resourseTypes_ = resourseTypes;
    itemNum_ = itemNum;
    board_ = board;
}

void KnightCard ::activate(Player *player)
{
    if (!player->hasRequiredResources({ResourceType::ORE, ResourceType::GRAIN, ResourceType::WOOL}))
    {
        std::cerr << "Player does not have the right resources" << std::endl;
        return;
    }
    if (player->getKnightCardsNum() == 3)
    {
        std::cerr << "too much knight cards..." << std::endl;
        return;
    }
    player->addKnightCard();
    player->deductResources({{ResourceType::ORE, 1}, {ResourceType::GRAIN, 1}, {ResourceType::WOOL, 1}});

    if (player->getKnightCardsNum() == 3)
    {
        player->addPoint(2);
    }
}

void VictoryCard ::activate(Player *player)
{
    if (!player->hasRequiredResources({ResourceType::ORE, ResourceType::GRAIN, ResourceType::WOOL}))
    {
        std::cerr << "Player does not have the right resources" << std::endl;
        return;
    }
    player->addPoint(1);
    player->deductResources({{ResourceType::ORE, 1}, {ResourceType::GRAIN, 1}, {ResourceType::WOOL, 1}});
}

void MonopolyCard ::activate(Player *player)
{
    if (!player->hasRequiredResources({ResourceType::ORE, ResourceType::GRAIN, ResourceType::WOOL}))
    {
        std::cerr << "Player does not have the right resources" << std::endl;
        return;
    }
    for (Player *p : catan_->getPlayersList())
    {

        int numOfResorce = p->getResorceCount(resource_);
        p->addAndSubResource(resource_, -numOfResorce);
        player->addAndSubResource(resource_, numOfResorce);
        player->deductResources({{ResourceType::ORE, 1}, {ResourceType::GRAIN, 1}, {ResourceType::WOOL, 1}});
    }
}
void MonopolyCard::setResource(ResourceType resource, Catan *catan)
{
    resource_ = resource;
    catan_ = catan;
}

void YearOfPlenty ::activate(Player *player)
{
    if (!player->hasRequiredResources({ResourceType::ORE, ResourceType::GRAIN, ResourceType::WOOL}))
    {
        std::cerr << "Player does not have the right resources" << std::endl;
        return;
    }
    player->addAndSubResource(resource1_, 1);
    player->addAndSubResource(resource2_, 1);
    player->deductResources({{ResourceType::ORE, 1}, {ResourceType::GRAIN, 1}, {ResourceType::WOOL, 1}});
}
void YearOfPlenty::setResources(ResourceType resource1, ResourceType resource2)
{
    resource1_ = resource1;
    resource2_ = resource2;
}
