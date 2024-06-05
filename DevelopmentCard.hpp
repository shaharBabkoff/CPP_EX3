#ifndef DEVELOPMENT_CARD_HPP
#define DEVELOPMENT_CARD_HPP
#include <vector>
#include "Hexigon.hpp"
#include "Catan.hpp"
class Board; // Forward declaration instead of #include "Board.hpp"
//enum class ResourceType;
class Player; // Forward declaration
class Catan;

class DevelopmentCard
{
public:
    virtual void activate(Player *player)= 0;;
    virtual ~DevelopmentCard();
};

class RoadBuildingCard : public DevelopmentCard
{
private:
    std::vector<ResourceType> resourseTypes_;
    std::vector<int> itemNum_;
    Board *board_;

public:
    RoadBuildingCard();
    void set2roads(std::vector<ResourceType> resourseTypes, std::vector<int> itemNum, Board *board);
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
    ResourceType resource_;
    Catan *catan_;

public:
    void setResource(ResourceType resource, Catan *catan);
    void activate(Player *player) override;
};
class YearOfPlenty : public DevelopmentCard
{
private:
    ResourceType resource1_;
    ResourceType resource2_;

public:
    void setResources(ResourceType resource1, ResourceType resource2);
    void activate(Player *player) override;
};
#endif // DEVELOPMENT_CARD_HPP