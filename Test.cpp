#include "doctest.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include "Board.hpp"
#include "Catan.hpp"
#include "Player.hpp"
#include <functional>
#include "Hexigon.hpp"

// #include "DevelopmentCard.hpp"
using namespace std;
Player Amit("Amit", 1);
Player Yossi("Yossi", 2);
Player Dana("Dana", 3);
Catan gameInstance(&Amit, &Yossi, &Dana);
Board &board = gameInstance.getBoard();

TEST_CASE("start game")
{
    CHECK(gameInstance.getCurrentPlayerIndex() == 1); // the starthing player is player 1
    CHECK(Amit.totalResources() == 0);         // the players dont have any resources
    CHECK(Yossi.totalResources() == 0);
    CHECK(Dana.totalResources() == 0);
    CHECK(board.getVerticesList().size() == 54); // the board has the right amount of vertices
    CHECK(board.getHexigonsList().size() == 37);
    // check that player cannot build city before he has settelments built...
    CHECK_THROWS_WITH(Amit.placeCity({ResourceType::ORE, ResourceType::BRICK, ResourceType::GRAIN}, {10, 6, 12}, board), "Error: player can not build city before he has at list 2 settelments..."); // the board has the right amount of hexigons

    Amit.placeSettelemnt({ResourceType::ORE, ResourceType::BRICK, ResourceType::GRAIN}, {10, 6, 12}, board); // vertex 8
    Amit.placeRoad({ResourceType::ORE, ResourceType::BRICK}, {10, 6}, board);                                // edge(8,9)
    Amit.placeSettelemnt({ResourceType::SEA, ResourceType::WOOL, ResourceType::ORE}, {2, 2, 10}, board);     // vertex 1
    Amit.placeRoad({ResourceType::ORE, ResourceType::WOOL}, {10, 2}, board);                                 // edge (1,9)
    Amit.endTurn(&gameInstance);
    CHECK(Amit.playerStatusString() == "Amit resources: brick: 1 ore: 2 lumber: 0 grain: 1 wool: 1 knight cards: 0 city: 0 settelment: 2 road: 2 points: 2");
    CHECK(gameInstance.getCurrentPlayerIndex() == 2);
    Yossi.placeSettelemnt({ResourceType::LUMBER, ResourceType::ORE, ResourceType::LUMBER}, {11, 3, 8}, board); // vertex 30
    Yossi.placeRoad({ResourceType::LUMBER, ResourceType::ORE}, {11, 3}, board);                                // road (30,31)
    Yossi.placeSettelemnt({ResourceType::ORE, ResourceType::GRAIN, ResourceType::GRAIN}, {3, 4, 6}, board);    // vertex 42
    Yossi.placeRoad({ResourceType::ORE, ResourceType::GRAIN}, {3, 4}, board);                                  // road (32,42)
    Yossi.endTurn(&gameInstance);
    CHECK(Yossi.playerStatusString() == "Yossi resources: brick: 0 ore: 2 lumber: 2 grain: 2 wool: 0 knight cards: 0 city: 0 settelment: 2 road: 2 points: 2");
    CHECK(gameInstance.getCurrentPlayerIndex() == 3);
    Dana.placeSettelemnt({ResourceType::LUMBER, ResourceType::BRICK, ResourceType::WOOL}, {9, 10, 4}, board); // vertex  12
    Dana.placeRoad({ResourceType::WOOL, ResourceType::BRICK}, {4, 10}, board);                                // road (12,22)
    Dana.placeSettelemnt({ResourceType::WOOL, ResourceType::LUMBER, ResourceType::NONE}, {4, 3, 0}, board);   // vertex 21
    Dana.placeRoad({ResourceType::NONE, ResourceType::LUMBER}, {0, 3}, board);                                // road (21,33)
    Dana.endTurn(&gameInstance);
    CHECK(Dana.playerStatusString() == "Dana resources: brick: 1 ore: 0 lumber: 2 grain: 0 wool: 2 knight cards: 0 city: 0 settelment: 2 road: 2 points: 2");
    CHECK(gameInstance.getCurrentPlayerIndex() == 1); // back to player 1 (Amit)
}

TEST_CASE("Testing Player::placeSettlement")
{
    // Amit resources: brick: 1 ore: 2 lumber: 0 grain: 1 wool: 1 knight cards: 0
    // city: 0 settelment: 2 road: 2
    // Yossi resources: brick: 0 ore: 2 lumber: 2 grain: 2 wool: 0 knight cards: 0
    // city: 0 settelment: 2 road: 2
    // Dana resources: brick: 1 ore: 0 lumber: 2 grain: 0 wool: 2 knight cards: 0
    // city: 0 settelment: 2 road: 2

    SUBCASE("Error when player has insufficient resources")
    {

        // Ensuring the player has no resources to trigger the first condition
        CHECK_THROWS_WITH(Amit.placeSettelemnt({ResourceType::ORE, ResourceType::BRICK, ResourceType::GRAIN}, {10, 6, 12}, board),
                          "Error: player does not have the right resources");
    }

    SUBCASE("Error when hexigons are not found")
    {
        // Setting up a scenario where the hexigons cannot be found
        Amit.addAndSubResource(ResourceType::LUMBER, 1); // adding Amit lumber so he can have the right resources
        CHECK_THROWS_WITH(Amit.placeSettelemnt({ResourceType::ORE, ResourceType::ORE, ResourceType::ORE}, {10, 6, 12}, board),
                          "Error: One or more hexigons not found");
    }

    SUBCASE("Error when no mutual vertex is found")
    {
        CHECK_THROWS_WITH(Amit.placeSettelemnt({ResourceType::LUMBER, ResourceType::BRICK, ResourceType::WOOL}, {11, 6, 2}, board),
                          "Error: No mutual vertex found");
    }
    SUBCASE("Error when vertex has neighboring settlements")
    {
        // This would require more complex state setup to simulate neighboring settlements
        CHECK_THROWS_WITH(Amit.placeSettelemnt({ResourceType::ORE, ResourceType::WOOL, ResourceType::BRICK}, {10, 2, 6}, board),
                          "Error: Vertex has neighbor settlement");
    }

    SUBCASE("Error when vertex does not have 2 roads")
    {
        // Assuming the player setup is such that there are not enough roads
        CHECK_THROWS_WITH(Amit.placeSettelemnt({ResourceType::SEA, ResourceType::LUMBER, ResourceType::WOOL}, {3, 9, 2}, board),
                          "Error: Vertex does not have 2 roads");
    }
    SUBCASE("succesfully building settelment")
    {
        // Amit resources: brick: 1 ore: 2 lumber: 1 grain: 1 wool: 1 knight cards: 0
        // city: 0 settelment: 2 road: 2
        Amit.addAndSubMultyResources({{ResourceType::LUMBER, 2}, {ResourceType::BRICK, 2}});
        Amit.placeRoad({ResourceType::GRAIN, ResourceType::BRICK}, {12, 6}, board);
        Amit.placeRoad({ResourceType::GRAIN, ResourceType::LUMBER}, {12, 11}, board); // building 2 roads
        Amit.placeSettelemnt({ResourceType::GRAIN, ResourceType::LUMBER, ResourceType::GRAIN}, {12, 11, 9}, board);
        // Amit has minus brick lumber grain and wool, (minus 2 lumber and 2 brick for the roads), plus 1 settelment (and 2 roads)
        CHECK(Amit.playerStatusString() == "Amit resources: brick: 0 ore: 2 lumber: 0 grain: 0 wool: 0 knight cards: 0 city: 0 settelment: 3 road: 4 points: 3");
        CHECK(Amit.getPlayerPoints() == 3);
    }
}
TEST_CASE("Testing Player::placeCity")
{
    SUBCASE("Error when player has insufficient resources")
    {

        // Ensuring the player has no resources to trigger the first condition
        CHECK_THROWS_WITH(Amit.placeSettelemnt({ResourceType::GRAIN, ResourceType::LUMBER, ResourceType::GRAIN}, {12, 11, 9}, board),
                          "Error: player does not have the right resources");
    }

    SUBCASE("Error:no settelment you own here")
    {
        // Setting up a scenario where the hexigons cannot be found
        Amit.addAndSubMultyResources({{ResourceType::ORE, 3}, {ResourceType::GRAIN, 2}});
        CHECK_THROWS_WITH(Amit.placeCity({ResourceType::LUMBER, ResourceType::BRICK, ResourceType::WOOL}, {9, 10, 4}, board),
                          "Error:no settelment you own here");
    }

    SUBCASE("succesfully building city")
    {

        Amit.placeCity({ResourceType::GRAIN, ResourceType::LUMBER, ResourceType::GRAIN}, {12, 11, 9}, board);
        // Amit has minus brick lumber grain and wool, (minus 2 lumber and 2 brick for the roads), plus 1 settelment (and 2 roads)
        CHECK(Amit.playerStatusString() == "Amit resources: brick: 0 ore: 2 lumber: 0 grain: 0 wool: 0 knight cards: 0 city: 1 settelment: 2 road: 4 points: 4");
        CHECK(Amit.getPlayerPoints() == 4);
    }
    SUBCASE("building on an existing city")
    {
        Amit.addAndSubMultyResources({{ResourceType::ORE, 3}, {ResourceType::GRAIN, 2}});

        // Amit has minus brick lumber grain and wool, (minus 2 lumber and 2 brick for the roads), plus 1 settelment (and 2 roads)
        CHECK_THROWS_WITH(Amit.placeCity({ResourceType::GRAIN, ResourceType::LUMBER, ResourceType::GRAIN}, {12, 11, 9}, board), "you already have a city here...");
    }
}
TEST_CASE("Testing Player::placeRoad")
{
    SUBCASE("Error when player has insufficient resources")
    {
        CHECK_THROWS_WITH(Amit.placeRoad({ResourceType::GRAIN, ResourceType::LUMBER}, {9, 11}, board),
                          "Error: Insufficient resources to build a road");
    }
    SUBCASE("Error: Road must connect to an existing road.")
    {
        Amit.addAndSubMultyResources({{ResourceType::BRICK, 1}, {ResourceType::LUMBER, 1}});

        CHECK_THROWS_WITH(Amit.placeRoad({ResourceType::BRICK, ResourceType::WOOL}, {6, 4}, board), "Error: Road must connect to an existing road.");
    }
    SUBCASE("Error: Edge already owned.")
    {
        CHECK_THROWS_WITH(Amit.placeRoad({ResourceType::GRAIN, ResourceType::LUMBER}, {12, 11}, board), "Error: Edge already owned.");
    }
    SUBCASE("succesfully building road")
    {
        Amit.placeRoad({ResourceType::GRAIN, ResourceType::LUMBER}, {9, 11}, board);
        CHECK(Amit.playerStatusString() == "Amit resources: brick: 0 ore: 5 lumber: 0 grain: 2 wool: 0 knight cards: 0 city: 1 settelment: 2 road: 5 points: 4");
    }
}

TEST_CASE("development cards")
{
    SUBCASE("knight card")
    {
       
        CHECK(Amit.playerStatusString()=="Amit resources: brick: 0 ore: 5 lumber: 0 grain: 2 wool: 0 knight cards: 0 city: 1 settelment: 2 road: 5 points: 4");
        CHECK_THROWS_WITH(gameInstance.getDevelopmentCard(CardType::KNIGHT, Amit), "Player does not have the right resources");
        Amit.addAndSubMultyResources({{ResourceType::WOOL, 5}, {ResourceType::ORE, 5}, {ResourceType::GRAIN, 3}});
        gameInstance.getDevelopmentCard(CardType::KNIGHT, Amit);
    
        gameInstance.getDevelopmentCard(CardType::KNIGHT, Amit);
        gameInstance.getDevelopmentCard(CardType::KNIGHT, Amit);
        // points now 6 (+2) and 3 knight cards
        CHECK(Amit.playerStatusString() == "Amit resources: brick: 0 ore: 7 lumber: 0 grain: 2 wool: 2 knight cards: 3 city: 1 settelment: 2 road: 5 points: 6");
        CHECK_THROWS_WITH(gameInstance.getDevelopmentCard(CardType::KNIGHT, Amit), "no valid card from your type");
    }
    SUBCASE("monopoly card")
    { 
        // Amit resources: brick: 1 ore: 2 lumber: 0 grain: 4 wool: 2 knight cards: 3
        //  city: 1 settelment: 2 road: 5
        //  Yossi resources: brick: 0 ore: 2 lumber: 2 grain: 2 wool: 0 knight cards: 0
        //  city: 0 settelment: 2 road: 2
        //  Dana resources: brick: 0 ore: 5 lumber: 2 grain: 0 wool: 2 knight cards: 0
        //  city: 0 settelment: 2 road: 2
        MonopolyCard *mc1 = dynamic_cast<MonopolyCard *>(gameInstance.getDevelopmentCard(CardType::MONOPOLY, Amit));
        mc1->setResource(ResourceType::LUMBER);
        mc1->activate(&Amit);
        // all the lumber at amit
        CHECK(Amit.playerStatusString() == "Amit resources: brick: 0 ore: 6 lumber: 4 grain: 1 wool: 1 knight cards: 3 city: 1 settelment: 2 road: 5 points: 6");
        CHECK(Dana.playerStatusString() == "Dana resources: brick: 1 ore: 0 lumber: 0 grain: 0 wool: 2 knight cards: 0 city: 0 settelment: 2 road: 2 points: 2");
        CHECK(Yossi.playerStatusString() == "Yossi resources: brick: 0 ore: 2 lumber: 0 grain: 2 wool: 0 knight cards: 0 city: 0 settelment: 2 road: 2 points: 2");
        MonopolyCard *mc2 = dynamic_cast<MonopolyCard *>(gameInstance.getDevelopmentCard(CardType::MONOPOLY, Amit));
        // must set the resource first
        CHECK_THROWS_WITH(mc2->activate(&Amit), "you need first to set your source");
    }
    SUBCASE("roads card")
    {
         CHECK_THROWS_WITH(gameInstance.getDevelopmentCard(CardType::ROADS, Amit), "Player does not have the right resources");
         Amit.addAndSubMultyResources({{ResourceType::WOOL, 8}, {ResourceType::ORE, 8}, {ResourceType::GRAIN, 8}});
        gameInstance.getDevelopmentCard(CardType::ROADS, Amit)->activate(&Amit);
       
        
        gameInstance.getDevelopmentCard(CardType::ROADS, Amit)->activate(&Amit);
        gameInstance.getDevelopmentCard(CardType::ROADS, Amit)->activate(&Amit);
        Amit.placeRoad({ResourceType::ORE, ResourceType::GRAIN}, {10, 12}, board);
        Amit.placeRoad({ResourceType::SEA, ResourceType::GRAIN}, {18, 12}, board);
        Amit.placeRoad({ResourceType::SEA, ResourceType::GRAIN}, {17, 12}, board);
        Amit.placeRoad({ResourceType::SEA, ResourceType::GRAIN}, {17, 9}, board);
        Amit.placeRoad({ResourceType::SEA, ResourceType::GRAIN}, {16, 9}, board);
        Amit.placeRoad({ResourceType::SEA, ResourceType::GRAIN}, {15, 9}, board);
        // 6 more lumber and 6 more brick
        CHECK(Amit.playerStatusString() == "Amit resources: brick: 0 ore: 10 lumber: 4 grain: 5 wool: 5 knight cards: 3 city: 1 settelment: 2 road: 11 points: 6");
        gameInstance.getDevelopmentCard(CardType::ROADS, Amit);

        // there is only 4 road cards
        CHECK_THROWS_WITH(gameInstance.getDevelopmentCard(CardType::ROADS, Amit)->activate(&Amit), "no valid card from your type");
    }
    SUBCASE("victory card")
    {
        gameInstance.getDevelopmentCard(CardType::VICTORY, Amit)->activate(&Amit);
        gameInstance.getDevelopmentCard(CardType::VICTORY, Amit)->activate(&Amit);
        gameInstance.getDevelopmentCard(CardType::VICTORY, Amit)->activate(&Amit);
        CHECK(Amit.getPlayerPoints() == 9);
      
    }
    SUBCASE("year of plenty card")
    {
        Amit.addAndSubMultyResources({{ResourceType::WOOL, 8}, {ResourceType::ORE, 8}, {ResourceType::GRAIN, 8}});
        YearOfPlenty *yc1 = dynamic_cast<YearOfPlenty *>(gameInstance.getDevelopmentCard(CardType::YEAR_OF_PLENTY, Amit));
        yc1->setResources(ResourceType::LUMBER, ResourceType::BRICK);
        yc1->activate(&Amit);
        Amit.printDevelopmentCardsMap();
        // all the lumber at amit
        CHECK(Amit.playerStatusString() == "Amit resources: brick: 1 ore: 13 lumber: 5 grain: 8 wool: 8 knight cards: 3 city: 1 settelment: 2 road: 11 points: 9");

        YearOfPlenty *yc2 = dynamic_cast<YearOfPlenty *>(gameInstance.getDevelopmentCard(CardType::YEAR_OF_PLENTY, Amit));
        // must set the resource first
        CHECK_THROWS_WITH(yc2->activate(&Amit), "you need first to set your resources");
    }
}
TEST_CASE("trade")
{
    SUBCASE("player trade with himself")
    {
        CHECK_THROWS_WITH(Amit.trade(Amit, ResourceType::BRICK, ResourceType::BRICK, 1, 1), "player cant trade with himself");
    }
    SUBCASE("one of the players doesnt have the right resource")
    {
        // Dana doesnt have
        CHECK_THROWS_WITH(Amit.trade(Dana, ResourceType::ORE, ResourceType::BRICK, 5, 3), "one of the players dont have the wanted resource");
        // Amit doesnt have
        CHECK_THROWS_WITH(Amit.trade(Dana, ResourceType::ORE, ResourceType::BRICK, 4, 2), "one of the players dont have the wanted resource");
    }
    SUBCASE("trade ended succesfully")
    {
        Amit.trade(Dana, ResourceType::LUMBER, ResourceType::BRICK, 5, 1);
        CHECK(Amit.playerStatusString() == "Amit resources: brick: 2 ore: 12 lumber: 0 grain: 7 wool: 7 knight cards: 3 city: 1 settelment: 2 road: 11 points: 9");
        CHECK(Dana.playerStatusString() == "Dana resources: brick: 0 ore: 0 lumber: 5 grain: 0 wool: 2 knight cards: 0 city: 0 settelment: 2 road: 2 points: 2");
    }
    SUBCASE("trade with development cards")
    {

        Amit.endTurn(&gameInstance);
        Yossi.addAndSubMultyResources({{ResourceType::WOOL, 2}, {ResourceType::ORE, 2}, {ResourceType::GRAIN, 2}});
        YearOfPlenty *yc1 = dynamic_cast<YearOfPlenty *>(gameInstance.getDevelopmentCard(CardType::YEAR_OF_PLENTY, Yossi));
        MonopolyCard *mc1 = dynamic_cast<MonopolyCard *>(gameInstance.getDevelopmentCard(CardType::MONOPOLY, Yossi));
        Yossi.trade(Amit, CardType::YEAR_OF_PLENTY, CardType::KNIGHT);
        CHECK(Amit.getPlayerPoints()==7);//as now he doesnt have 3 knights
        Yossi.trade(Amit, CardType::MONOPOLY, CardType::ROADS);
        CHECK(Yossi.getCardNum(CardType::KNIGHT) == 1);
        CHECK(Yossi.getCardNum(CardType::ROADS) == 1);
        CHECK(Amit.getCardNum(CardType::KNIGHT) == 2);
        CHECK(Amit.getCardNum(CardType::YEAR_OF_PLENTY) == 2);
        CHECK(Amit.getCardNum(CardType::MONOPOLY) == 2);
        yc1->setResources(ResourceType::LUMBER, ResourceType::BRICK);
        mc1->setResource(ResourceType::LUMBER);
        Amit.setPlayerTurn(true);
        yc1->activate(&Amit);
        mc1->activate(&Amit);
        CHECK(Amit.getCardNum(CardType::MONOPOLY) == 1);
        CHECK(Amit.getCardNum(CardType::YEAR_OF_PLENTY) == 1);
        Amit.printDevelopmentCardsMap();
        cout<<"Amit points: "<<Amit.getPlayerPoints();
    }
}

TEST_CASE("roll dice")
{

    // Amit resources: brick: 3 ore: 5 lumber: 6 grain: 0 wool: 0 knight cards: 3
    //  city: 1 settelment: 2 road: 11
    //  Dana resources: brick: 0 ore: 0 lumber: 0 grain: 0 wool: 2 knight cards: 0
    //  city: 0 settelment: 2 road: 2
    //  Yossi resources: brick: 0 ore: 4 lumber: 0 grain: 4 wool: 2 knight cards: 0
    //  city: 0 settelment: 2 road: 2

    CHECK_THROWS_WITH(Dana.rollDice(board, &gameInstance, 10), "not player turn...");

    Amit.rollDice(board, &gameInstance, 6);
    Amit.rollDice(board, &gameInstance, 10);
    Amit.rollDice(board, &gameInstance, 8);
    CHECK(Amit.playerStatusString() == "Amit resources: brick: 4 ore: 14 lumber: 6 grain: 7 wool: 7 knight cards: 2 city: 1 settelment: 2 road: 11 points: 7");

    CHECK(Dana.playerStatusString() == "Dana resources: brick: 1 ore: 0 lumber: 0 grain: 0 wool: 2 knight cards: 0 city: 0 settelment: 2 road: 2 points: 2");

    CHECK(Yossi.playerStatusString() == "Yossi resources: brick: 0 ore: 2 lumber: 1 grain: 3 wool: 0 knight cards: 1 city: 0 settelment: 2 road: 2 points: 2");

    SUBCASE("rolled 7")
    {
        Amit.rollDice(board, &gameInstance, 7);
        CHECK(Amit.playerStatusString() == "Amit resources: brick: 0 ore: 14 lumber: 0 grain: 5 wool: 0 knight cards: 2 city: 1 settelment: 2 road: 11 points: 7");
        CHECK(Dana.playerStatusString() == "Dana resources: brick: 1 ore: 0 lumber: 0 grain: 0 wool: 2 knight cards: 0 city: 0 settelment: 2 road: 2 points: 2");
        CHECK(Yossi.playerStatusString() == "Yossi resources: brick: 0 ore: 2 lumber: 1 grain: 3 wool: 0 knight cards: 1 city: 0 settelment: 2 road: 2 points: 2");
    }
}
TEST_CASE("End game - Test winner announcement")
{
    Amit.trade(Yossi, CardType::YEAR_OF_PLENTY, CardType::KNIGHT);
    Amit.addAndSubMultyResources({{ResourceType::LUMBER,1},{ResourceType::BRICK,1},{ResourceType::WOOL,1}});
    Amit.placeSettelemnt({ResourceType::SEA, ResourceType::GRAIN, ResourceType::LUMBER}, {15, 9, 8}, board);
    CHECK(gameInstance.printWinner() == "Amit");
}
