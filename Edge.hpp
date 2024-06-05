#ifndef EDGE_HPP 
#define EDGE_HPP 
 
#include "Vertex.hpp" 
#include "Player.hpp" 
#include <iostream> 
 
class Edge 
{ 
private: 
    Vertex* vertex1_; 
    Vertex* vertex2_; 
    Player* owner_; 
 
public: 
    Edge(Vertex* ver1, Vertex* ver2) 
        : vertex1_(ver1), vertex2_(ver2), owner_(nullptr) // Initialize owner_ to nullptr 
    { 
        if (vertex1_ == nullptr || vertex2_ == nullptr) { 
            std::cerr << "Error: One or both vertices are null in Edge constructor!" << std::endl; 
        } 
    } 
    ~Edge(){}
 
    Vertex* getV1() const { return vertex1_; } 
    Vertex* getV2() const { return vertex2_; } 
 
    Vertex* getOtherVertex(Vertex* v) { 
        if (!v) { 
            std::cerr << "Null vertex passed to getOtherVertex" << std::endl; 
            return nullptr; 
        } 
        if (v == vertex1_) { 
            return vertex2_; 
        } else if (v == vertex2_) { 
            return vertex1_; 
        } else { 
            //std::cerr << "Vertex not part of this edge" << std::endl; 
            return nullptr; 
        } 
    } 
 
    Player* getEdgeOwner() const { 
        return owner_; 
    } 
 
    void setEdgeOwner(Player* owner) { 
        owner_ = owner; 
    } 
    std::vector<Hexigon*> getHexigons();
    std::vector<int>getCloseNumbers();
}; 
 
#endif // EDGE_HPP