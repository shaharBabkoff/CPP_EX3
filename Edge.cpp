//id:324207935 email:shbabkoff123@gmail.com
#include "Edge.hpp"
using namespace std;

Edge::Edge(Vertex *ver1, Vertex *ver2)
    : vertex1_(ver1), vertex2_(ver2), owner_(nullptr) // Initialize owner_ to nullptr
{
    if (vertex1_ == nullptr || vertex2_ == nullptr)
    {
        cerr << "Error: One or both vertices are null in Edge constructor!" << endl;
    }
}

Edge::~Edge() {}
Vertex *Edge::getV1() const { return vertex1_; }
Vertex *Edge::getV2() const { return vertex2_; }

Vertex *Edge::getOtherVertex(Vertex *v) const
{
    if (!v)
    {
        cerr << "Null vertex passed to getOtherVertex" << endl;
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