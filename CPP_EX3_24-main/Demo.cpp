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

  Player p1("Amit", 1);
  Player p2("Yossi", 2);
  Player p3("Dana", 3);
  Catan catan(&p1, &p2, &p3);
  // Starting of the game. Every player places two settlements and two roads.
  catan.ChooseStartingPlayer(); // should print the name of the starting player, assume it is Amit.
  // std::cout << std::boolalpha << p1.isPlayerTurn() << " checkkk" << std::endl;
  Board board = catan.getBoard(); // get the board of the game.
  // // board.printBoard();
  // p1.placeSettelemnt({ResourceType::ORE, ResourceType::BRICK, ResourceType::GRAIN}, {10, 6, 12}, board);
  // p1.placeRoad({ResourceType::ORE, ResourceType::BRICK}, {10, 6}, board);
  // p1.placeSettelemnt({ResourceType::SEA, ResourceType::WOOL, ResourceType::ORE}, {2, 2, 10}, board);
  // p1.placeRoad({ResourceType::ORE, ResourceType::WOOL}, {10, 2}, board);
  // p1.endTurn(catan);

  // p2.placeSettelemnt({ResourceType::LUMBER, ResourceType::ORE, ResourceType::LUMBER}, {11, 3, 8}, board);
  // p2.placeRoad({ResourceType::LUMBER, ResourceType::ORE}, {11, 3}, board);
  // p2.placeSettelemnt({ResourceType::ORE, ResourceType::GRAIN, ResourceType::GRAIN}, {3, 4, 6}, board);
  // p2.placeRoad({ResourceType::ORE, ResourceType::GRAIN}, {3, 4}, board);
  // p2.endTurn(catan);
  // p3.placeSettelemnt({ResourceType::LUMBER, ResourceType::BRICK, ResourceType::WOOL}, {9, 10, 4}, board);
  // p3.placeRoad({ResourceType::WOOL, ResourceType::BRICK}, {4, 10}, board);
  // p3.placeSettelemnt({ResourceType::WOOL, ResourceType::LUMBER, ResourceType::NONE}, {4, 3, 0}, board);
  // p3.placeRoad({ResourceType::NONE, ResourceType::LUMBER}, {0, 3}, board);
  // p3.endTurn(catan);
  // cout << "player 1 has " << p1.getPlayerEdgesList().size() << " roads" << endl;
  // cout << "player 2 has " << p1.getPlayerEdgesList().size() << " roads" << endl;
  // cout << "player 3 has " << p1.getPlayerEdgesList().size() << " roads" << endl;

  // p1.rollDice(board);                                                     // Lets say it's print 4. Then, p2 gets ore from the mountations.
  // p1.placeRoad({ResourceType::WOOL, ResourceType::BRICK}, {2, 6}, board); // p1 continues to build a road.
  // p1.endTurn(catan);
  // p2.rollDice(board);
  // p2.endTurn(catan);
  // p3.rollDice(board);
  // p3.placeRoad({ResourceType::WOOL, ResourceType::LUMBER}, {4, 3}, board);
  // p3.endTurn(catan);
  // p1.rollDice(board);
  // p1.endTurn(catan);
  // p2.rollDice(board);
  // p2.endTurn(catan);
  // p3.rollDice(board);
  // p3.endTurn(catan);
  // p1.addAndSubResource(ResourceType::GRAIN, 2);

  // p1.addAndSubResource(ResourceType::ORE, 3);

  // p1.placeCity({ResourceType::ORE, ResourceType::BRICK, ResourceType::GRAIN}, {10, 6, 12}, board);
  // cout << "player 1 has " << p1.getPlayerPoints() << " points" << endl;
  // cout << "player 2 has " << p1.getPlayerPoints() << " points" << endl;
  // cout << "player 3 has " << p1.getPlayerPoints() << " points" << endl;
  // catan.printPlayersStatus();
  // catan.printWinner();                                                // Should print None because no player reached 10 points.
  // std::unique_ptr<DevelopmentCard> &c1 = board.getDevelopmentCard(0); // knight card
  // c1->activate(&p1);
  // RoadBuildingCard card;
  // card.activate(&board);
}