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
     Hexigon(int number, ResourceType type, std::vector<int> verticesIds, std::vector<Vertex *> *vertices)
        : number_(number), vertices_(verticesIds.size(), nullptr), type_(type) // Initialize with 6 null pointers
    {
        std::vector<Vertex *> &tmp = *vertices; // Get reference to the vertices vector

        for (size_t i = 0; i < verticesIds.size(); i++) {
            int indexVertex = verticesIds[i];
            Vertex *v = tmp[indexVertex];
            vertices_[i] = v;
        }

        for (size_t i = 0; i < verticesIds.size() - 1; i++) {
            Edge *tmp1 = new Edge((*vertices)[verticesIds[i]], (*vertices)[verticesIds[i + 1]]);
            edges_.push_back(tmp1);
        }
        if (type != ResourceType::SEA) {
            Edge *tmp2 = new Edge((*vertices)[verticesIds[0]], (*vertices)[verticesIds[verticesIds.size() - 1]]);
            edges_.push_back(tmp2);
        }
    }
   ~Hexigon() {
    for (Edge* edge : edges_) {
        delete edge;  // Delete each dynamically allocated Edge
    }
    edges_.clear();  // Clear the vector after deleting all elements
}


    std::vector<Vertex *> getVerticesList() const
    {
        return vertices_;
    }
    std::vector<Edge *> getEdgesList() const
    {
        return edges_;
    }
    // std::vector<Edge *> getEdgesWithSpecificVertex(Vertex *v)
    // {
    //     std::vector<Edge *> ans;
    //     for (Edge *e : edges_)
    //     {
    //         if (e->getV1())
    //         {
    //             ans.push_back(e);
    //         }
    //         if (e->getV2())
    //         {
    //             ans.push_back(e);
    //         }
    //     }
    // }

    int getNumber() const
    {
        return number_;
    }
    ResourceType getType() const
    {
        return type_;
    }
};
#endif // HEXIGON_HPP
