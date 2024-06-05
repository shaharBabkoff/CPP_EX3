#ifndef HEXIGON_HPP
#define HEXIGON_HPP

#include <vector>
#include <iostream>
#include "Vertex.hpp"
#include "Edge.hpp"

enum class ResourceType
{
    LUMBER,
    BRICK,
    WOOL,
    GRAIN,
    ORE,
    NONE,
    SEA
};

class Hexigon
{
private:
    int number_;
    std::vector<Vertex *> vertices_; // 6 vertices
    ResourceType type_;
    std::vector<Edge *> edges_;

public:
    Hexigon(int number, ResourceType type, std::vector<int> verticesIds, std::vector<Vertex *> *vertices);
    ~Hexigon();
    std::vector<Vertex *> getVerticesList() const;
    std::vector<Edge *> getEdgesList() const;
    int getNumber() const;
    ResourceType getType() const;
};
#endif // HEXIGON_HPP
