#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <memory>
#include <random>
#include <algorithm>


#include "Hexigon.hpp" 
#include "Vertex.hpp"
#include "DevelopmentCard.hpp"


//class Hexigon; // Forward declaration
//class Vertex; // Forward declaration
//class DevelopmentCard; // Forward declaration
class Board
{
private:
   std::vector<Hexigon *> hexigons_; // 19 hexigons
   std::vector<Vertex *> vertices_;  // 54 vertices
  // std::vector<YearOfPlenty*> yopc_;
 // std::vector<std::unique_ptr<DevelopmentCard>> developmentCards_;
    //std::default_random_engine rng;  // Random number generator

public:
   Board();
   ~Board(); // Destructor to clean up dynamically allocated memory
   void initializeBoard();
   void updateVertexNeighbers();
   void initializHexigons();
   void initializeVertices();
  // DevelopmentCard* getRandomCard();
   // void shuffleCards();  // Shuffles the deck
  //void initializeDevelopmentCards();
   // void initializeEdges();
   // std::unique_ptr<DevelopmentCard>& getDevelopmentCard(int index)
   // {
   //   return developmentCards_[index];
   // }
   void printBoard();
   std::vector<Hexigon *> getHexigonsList();
   std::vector<Vertex *> getVerticesList();
  
};
#endif // BOARD_HPP