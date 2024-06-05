#ifndef EDGE_HPP
#define EDGE_HPP

#include "Vertex.hpp"
#include "Player.hpp"
#include <iostream>

class Edge
{
private:
    Vertex *vertex1_;
    Vertex *vertex2_;
    Player *owner_;

public:
    Edge(Vertex *ver1, Vertex *ver2);
    ~Edge();
    Vertex *getV1() const;
    Vertex *getV2() const;
    Vertex *getOtherVertex(Vertex *v) const;
    Player *getEdgeOwner() const;
    void setEdgeOwner(Player *owner);
};

#endif // EDGE_HPP