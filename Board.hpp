#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <memory>
#include <random>
#include <algorithm>
#include "Hexigon.hpp" 
#include "Vertex.hpp"
#include "DevelopmentCard.hpp"

// Board class represents the game board of Catan, managing the hexigons and vertices
// which constitute the physical layout and logical functionality of the game board.
class Board
{
private:
   std::vector<Hexigon *> hexigons_; // Stores pointers to Hexigon objects that represent each hexagonal tile on the board.
   std::vector<Vertex *> vertices_;  // Stores pointers to Vertex objects that represent each vertex or intersection on the board.

public:
   // Constructor: Initializes an empty game board with a fixed number of vertices and space for hexigons.
   Board();
   
   // Destructor: Cleans up memory allocated for hexigons and vertices to prevent memory leaks.
   ~Board(); // Assuming this is a typo and should be ~Board();

   // Initializes hexigons on the board with specific resource types and positions.
   // This setup is specific to the standard layout of the Catan board or can be randomized.
   void initializHexigons();

   // Initializes vertices on the board, associating each with an index for reference.
   // Vertices are points where players can build settlements or cities.
   void initializeVertices();

   // Prints a visual representation of the board's current state in the console,
   // showing hexigons and their associated resources and vertices.
   void printBoard();

   // Returns a const reference to the vector of hexigons, allowing external access
   // without modifying the board's hexigon configuration.
   std::vector<Hexigon *> getHexigonsList() const;

   // Returns a const reference to the vector of vertices, allowing external access
   // without modifying the board's vertex configuration.
   std::vector<Vertex *> getVerticesList() const;
};

#endif // BOARD_HPP
