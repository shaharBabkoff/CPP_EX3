//id:324207935 email:shbabkoff123@gmail.com
#include "Vertex.hpp"
using namespace std;

// Constructor: Initializes a Vertex with a given id.
// Sets the owner to nullptr and the populated entity to NONE by default.
Vertex::Vertex(int id) : id_(id), vertexOwner_(nullptr), populatedEntity_(PopulatedEntity::NONE) {}

// Destructor: Default destructor. There's no dynamic memory directly managed within this class,
// so the body is empty.
Vertex::~Vertex() {}

// Adds a neighboring Hexigon to this vertex.
// This function is typically called when constructing the game board to link each vertex
// to the hexigons that surround it.
void Vertex::addNeighbor(Hexigon *h)
{
    surroundedHexigons_.push_back(h);
}

// Returns the identifier of the vertex.
int Vertex::getId() const { return id_; }

// Returns the player who owns this vertex, if any.
// Returns nullptr if the vertex is not owned by any player.
Player *Vertex::getVertexOwner() const { return vertexOwner_; }

// Returns the type of entity (NONE, SETTLEMENT, or CITY) that is located at this vertex.
PopulatedEntity Vertex::getPopulatedEntity() const { return populatedEntity_; }

// Provides read-only access to the vector of Hexigons that surround this vertex.
// Useful for determining resource production and game logic related to the vertex location.
const vector<Hexigon *> &Vertex::getSurroundedHexigons() const { return surroundedHexigons_; }

// Sets the owner of this vertex to a specific player.
// This function is called when a player builds a settlement or city at this vertex.
void Vertex::setVertexOwner(Player *owner) { vertexOwner_ = owner; }

// Sets the type of populated entity at this vertex.
// This is used to upgrade the vertex to hold a settlement or city.
void Vertex::setPopulatedEntity(PopulatedEntity entity) { populatedEntity_ = entity; }
