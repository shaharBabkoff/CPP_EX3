//id:324207935 email:shbabkoff123@gmail.com
#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <vector>
#include <map>

class Player;  // Forward declaration
class Hexigon; // Forward declaration

enum class PopulatedEntity
{
    NONE,
    SETTLEMENT,
    CITY
};

class Vertex
{
private:
    int id_;
    Player *vertexOwner_;
    PopulatedEntity populatedEntity_;
    std::vector<Hexigon *> surroundedHexigons_;

public:
    Vertex(int id);
    ~Vertex();
    void addNeighbor(Hexigon *h);
    int getId() const;
    Player *getVertexOwner() const;
    PopulatedEntity getPopulatedEntity() const;
    const std::vector<Hexigon *> &getSurroundedHexigons() const;
    void setVertexOwner(Player *owner);
    void setPopulatedEntity(PopulatedEntity entity);
};

#endif // VERTEX_HPP
