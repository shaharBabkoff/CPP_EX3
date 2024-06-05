#include "Edge.hpp"

Edge::Edge(Vertex *ver1, Vertex *ver2)
    : vertex1_(ver1), vertex2_(ver2), owner_(nullptr) // Initialize owner_ to nullptr
{
    if (vertex1_ == nullptr || vertex2_ == nullptr)
    {
        std::cerr << "Error: One or both vertices are null in Edge constructor!" << std::endl;
    }
}

Edge::~Edge() {}
Vertex *Edge::getV1() const { return vertex1_; }
Vertex *Edge::getV2() const { return vertex2_; }

Vertex *Edge::getOtherVertex(Vertex *v) const
{
    if (!v)
    {
        std::cerr << "Null vertex passed to getOtherVertex" << std::endl;
        return nullptr;
    }
    if (v == vertex1_)
    {
        return vertex2_;
    }
    else if (v == vertex2_)
    {
        return vertex1_;
    }
    else
    {
        // std::cerr << "Vertex not part of this edge" << std::endl;
        return nullptr;
    }
}

Player *Edge::getEdgeOwner() const
{
    return owner_;
}

void Edge::setEdgeOwner(Player *owner)
{
    owner_ = owner;
}