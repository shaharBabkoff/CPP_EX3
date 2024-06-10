/**
 * Demo file for Ex3.
 *
 */
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Board.hpp"
#include "Catan.hpp"
#include "Player.hpp"

#include "Hexigon.hpp"
// #include "DevelopmentCard.hpp"
using namespace std;
// using namespace ariel;

int main()
{

  Player Amit("Amit", 1);
  Player Yossi("Yossi", 2);
  Player Dana("Dana", 3);
  Catan catan(&Amit, &Yossi, &Dana);
  // Starting of the game. Every player places two settlements and two roads.
  // catan.ChooseStartingPlayer(); // should print the name of the starting player, assume it is Amit.
  // std::cout << std::boolalpha << Amit.isPlayerTurn() << " checkkk" << std::endl;
  Board &board = catan.getBoard(); // get the board of the game.
  // board.printBoard();

  Amit.placeSettelemnt({ResourceType::ORE, ResourceType::BRICK, ResourceType::GRAIN}, {10, 6, 12}, board); // vertex 8
  Amit.placeRoad({ResourceType::ORE, ResourceType::BRICK}, {10, 6}, board);                                // edge(8,9)
  Amit.placeSettelemnt({ResourceType::SEA, ResourceType::WOOL, ResourceType::ORE}, {2, 2, 10}, board);     // vertex 1
  Amit.placeRoad({ResourceType::ORE, ResourceType::WOOL}, {10, 2}, board);                                 // edge (1,9)
  Amit.endTurn(&catan);
  Amit.printPlayerStatus();

  Yossi.placeSettelemnt({ResourceType::LUMBER, ResourceType::ORE, ResourceType::LUMBER}, {11, 3, 8}, board); // vertex 30
  Yossi.placeRoad({ResourceType::LUMBER, ResourceType::ORE}, {11, 3}, board);                                // road (30,31)
  Yossi.placeSettelemnt({ResourceType::ORE, ResourceType::GRAIN, ResourceType::GRAIN}, {3, 4, 6}, board);    // vertex 42
  Yossi.placeRoad({ResourceType::ORE, ResourceType::GRAIN}, {3, 4}, board);                                  // road (32,42)
  Yossi.endTurn(&catan);
  Yossi.printPlayerStatus();

  Dana.placeSettelemnt({ResourceType::LUMBER, ResourceType::BRICK, ResourceType::WOOL}, {9, 10, 4}, board); // vertex  12
  Dana.placeRoad({ResourceType::WOOL, ResourceType::BRICK}, {4, 10}, board);                                // road (12,22)
  Dana.placeSettelemnt({ResourceType::WOOL, ResourceType::LUMBER, ResourceType::NONE}, {4, 3, 0}, board);   // vertex 21
  Dana.placeRoad({ResourceType::NONE, ResourceType::LUMBER}, {0, 3}, board);                                // road (21,33)
  Dana.endTurn(&catan);
  Dana.printPlayerStatus();

  Amit.rollDice(board, &catan, 6);
  Amit.addAndSubMultyResources({{ResourceType::GRAIN, 5}, {ResourceType::ORE, 5}, {ResourceType::WOOL, 5}});
  KnightCard *rbc1 = dynamic_cast<KnightCard *>(catan.getDevelopmentCard(CardType::KNIGHT, Amit));

  Amit.endTurn(&catan);
  Yossi.rollDice(board, &catan, 6);
  Yossi.addAndSubMultyResources({{ResourceType::GRAIN, 5}, {ResourceType::ORE, 5}, {ResourceType::WOOL, 5}});
  RoadBuildingCard *rbc2 = dynamic_cast<RoadBuildingCard *>(catan.getDevelopmentCard(CardType::ROADS, Yossi));

  Yossi.trade(Amit, CardType::ROADS, CardType::KNIGHT);
  YearOfPlenty *yc1 = dynamic_cast<YearOfPlenty *>(catan.getDevelopmentCard(CardType::YEAR_OF_PLENTY, Yossi));
  yc1->setResources(ResourceType::LUMBER, ResourceType::BRICK);
  yc1->activate(&Yossi);
  Yossi.endTurn(&catan);
}