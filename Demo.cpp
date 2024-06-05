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
  catan.ChooseStartingPlayer(); // should print the name of the starting player, assume it is Amit.
  // std::cout << std::boolalpha << Amit.isPlayerTurn() << " checkkk" << std::endl;
  Board *board = catan.getBoard(); // get the board of the game.
  // board.printBoard();
  Amit.placeSettelemnt({ResourceType::ORE, ResourceType::BRICK, ResourceType::GRAIN}, {10, 6, 12}, board);
  Amit.placeRoad({ResourceType::ORE, ResourceType::BRICK}, {10, 6}, board);
  Amit.placeSettelemnt({ResourceType::SEA, ResourceType::WOOL, ResourceType::ORE}, {2, 2, 10}, board);
  Amit.placeRoad({ResourceType::ORE, ResourceType::WOOL}, {10, 2}, board);
  Amit.endTurn(&catan);

  Yossi.placeSettelemnt({ResourceType::LUMBER, ResourceType::ORE, ResourceType::LUMBER}, {11, 3, 8}, board);
  Yossi.placeRoad({ResourceType::LUMBER, ResourceType::ORE}, {11, 3}, board);
  Yossi.placeSettelemnt({ResourceType::ORE, ResourceType::GRAIN, ResourceType::GRAIN}, {3, 4, 6}, board);
  Yossi.placeRoad({ResourceType::ORE, ResourceType::GRAIN}, {3, 4}, board);
  Yossi.endTurn(&catan);

  Dana.placeSettelemnt({ResourceType::LUMBER, ResourceType::BRICK, ResourceType::WOOL}, {9, 10, 4}, board);
  Dana.placeRoad({ResourceType::WOOL, ResourceType::BRICK}, {4, 10}, board);
  Dana.placeSettelemnt({ResourceType::WOOL, ResourceType::LUMBER, ResourceType::NONE}, {4, 3, 0}, board);
  Dana.placeRoad({ResourceType::NONE, ResourceType::LUMBER}, {0, 3}, board);
  Dana.endTurn(&catan);
  // cout << "player 1 has " << Amit.getPlayerEdgesList().size() << " roads" << endl;
  // cout << "player 2 has " << Amit.getPlayerEdgesList().size() << " roads" << endl;
  // cout << "player 3 has " << Amit.getPlayerEdgesList().size() << " roads" << endl;

  Amit.rollDice(board,6);                                                   
  //Amit.placeRoad({ResourceType::WOOL, ResourceType::BRICK}, {2, 6}, board); // probbably not enoghth resources
  Amit.endTurn(&catan);

  Yossi.rollDice(board);
  Yossi.placeRoad({ResourceType::LUMBER, ResourceType::NONE}, {11, 0}, board);
  Yossi.endTurn(&catan);

  Dana.rollDice(board);
  Dana.placeRoad({ResourceType::WOOL, ResourceType::LUMBER}, {4, 3}, board);
  Dana.endTurn(&catan);

  Amit.rollDice(board);
  Amit.endTurn(&catan);

  Yossi.rollDice(board);
  Yossi.endTurn(&catan);

  Dana.rollDice(board);
  Dana.endTurn(&catan);
  Amit.addAndSubResource(ResourceType::GRAIN, 2);

  Amit.addAndSubResource(ResourceType::ORE, 3);

  Amit.placeCity({ResourceType::ORE, ResourceType::BRICK, ResourceType::GRAIN}, {10, 6, 12}, board);
  cout << "player 1 has " << Amit.getPlayerPoints() << " points" << endl;
  cout << "player 2 has " << Amit.getPlayerPoints() << " points" << endl;
  cout << "player 3 has " << Amit.getPlayerPoints() << " points" << endl;
  catan.printPlayersStatus();
  catan.printWinner();                                                // Should print None because no player reached 10 points.
  // std::unique_ptr<DevelopmentCard> &c1 = board.getDevelopmentCard(0); // knight card
  // c1->activate(&Amit);
  // RoadBuildingCard card;
  // card.activate(&board);
}