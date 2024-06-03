#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <vector>
#include <map>

class Player; // Forward declaration
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
    PopulatedEntity populatedEntity_ ;
    std::vector<Hexigon*> surroundedHexigons_;

public:
    Vertex(int id) : id_(id), vertexOwner_(nullptr), populatedEntity_(PopulatedEntity::NONE) {}

    void addNeighbor(Hexigon* h) {
        surroundedHexigons_.push_back(h);
    }
    
    int getId() const { return id_; }
    Player* getVertexOwner() const { return vertexOwner_; }
    PopulatedEntity getPopulatedEntity() const { return populatedEntity_; }
    const std::vector<Hexigon*>& getSurroundedHexigons() const { return surroundedHexigons_; }

    void setVertexOwner(Player* owner) { vertexOwner_ = owner; }
    void setPopulatedEntity(PopulatedEntity entity) { populatedEntity_ = entity; }
};

#endif // VERTEX_HPP
