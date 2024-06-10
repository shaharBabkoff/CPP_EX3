#include "Hexigon.hpp"
using namespace std;
// Constructor: Initializes a Hexigon with a number, resource type, and associated vertex IDs.
// 'vertices' is a pointer to a vector containing all vertices on the board.
Hexigon::Hexigon(int number, ResourceType type, vector<int> verticesIds, vector<Vertex *> *vertices)
    : number_(number), vertices_(verticesIds.size(), nullptr), type_(type) // Initialize with 6 null pointers
{
    vector<Vertex *> &tmp = *vertices; // Get reference to the vertices vector
                                       // Assign the correct vertex pointers from the global list to this hexagon's vertices.
    for (size_t i = 0; i < verticesIds.size(); i++)
    {
        int indexVertex = verticesIds[i];
        Vertex *v = tmp[indexVertex];
        vertices_[i] = v;
    }
    // Create edges between consecutive vertices, assuming vertices are listed in order.
    for (size_t i = 0; i < verticesIds.size() - 1; i++)
    {
        Edge *tmp1 = new Edge((*vertices)[verticesIds[i]], (*vertices)[verticesIds[i + 1]]);
        edges_.push_back(tmp1);
    }
    // If the hexagon is not of type SEA, link the first and last vertices to close the polygon.
    if (type != ResourceType::SEA)
    {
        Edge *tmp2 = new Edge((*vertices)[verticesIds[0]], (*vertices)[verticesIds[verticesIds.size() - 1]]);
        edges_.push_back(tmp2);
    }
}

// Destructor: Cleans up dynamically allocated Edges to prevent memory leaks.
Hexigon::~Hexigon()
{
    for (Edge *edge : edges_)
    {
        delete edge; // Delete each dynamically allocated Edge
    }
    edges_.clear(); // Clear the vector after deleting all elements
}

vector<Vertex *> Hexigon::getVerticesList() const
{
    return vertices_;
}
vector<Edge *> Hexigon::getEdgesList() const
{
    return edges_;
}

int Hexigon::getNumber() const
{
    return number_;
}
ResourceType Hexigon::getType() const
{
    return type_;
}