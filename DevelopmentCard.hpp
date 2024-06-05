#ifndef DEVELOPMENT_CARD_HPP
#define DEVELOPMENT_CARD_HPP
#include <vector>
#include "Hexigon.hpp"
class Player; // Forward declaration

class DevelopmentCard
{

public:
    bool isUsed_;
    virtual void activate(Player *player) = 0;
    virtual ~DevelopmentCard();
    bool getIfIsUsed();
    void activateFirstCheck(Player *player);
    void activateEnd(Player* player);
};

class RoadBuildingCard : public DevelopmentCard
{
    void activate(Player *player) override;
};

class KnightCard : public DevelopmentCard
{
public:
    void activate(Player *player) override;
};
class VictoryCard : public DevelopmentCard
{
public:
    void activate(Player *player) override;
};
class MonopolyCard : public DevelopmentCard
{
private:
    ResourceType resource_ = ResourceType::NONE;
    std::vector<Player *> playersList_;

public:
    MonopolyCard(std::vector<Player *> playersList);
    void setResource(ResourceType resource);
    void activate(Player *player) override;
};
class YearOfPlenty : public DevelopmentCard
{
private:
    ResourceType resource1_ = ResourceType::NONE;
    ResourceType resource2_ = ResourceType::NONE;

public:
    void activate(Player *player) override;
    void setResources(ResourceType resource1, ResourceType resource2);
};
#endif // DEVELOPMENT_CARD_HPP