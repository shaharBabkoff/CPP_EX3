//id:324207935 email:shbabkoff123@gmail.com
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "Vertex.hpp"
#include "DevelopmentCard.hpp"
#include "ResourceTypes.hpp"
class Edge;
class Board;
class Catan;
class KnightCard;

class Player
{
private:
  std::string name_;
  int points_ = 0;
  std::vector<Vertex *> verticesList_;
  std::vector<Edge *> edgesList_;
  std::map<ResourceType, int> resourceCards_;
  bool isPlayerTurn_ = false; // Initialize to false
  int playerIndex_;
  std::map<CardType, int> developmentCardsMap_;

public:
  Player(std::string name, int index);
  ~Player(); // Destructor
  void addAndRemoveCard(CardType type, int num);
  std::map<CardType, int> getDevelopmentCardsMap();
  int getCardNum(CardType type) ;
  std::string getPlayerName() const;
  std::vector<Vertex *> getPlayerVerticesList() const ;
  std::vector<Edge *> getPlayerEdgesList() const;
  int getPlayerPoints() const ;
  void addAndSubResource(ResourceType resource, int num);
  int getResorceCount(ResourceType resource) ;
  std::string playerStatusString();
  int totalResources() const;
  void addVertex(Vertex *v) { verticesList_.push_back(v); }
  void addEdge(Edge *e) { edgesList_.push_back(e); }
  void setPlayerTurn(bool turn) { isPlayerTurn_ = turn; }
  bool hasRequiredResources(const std::vector<ResourceType> &resources);
//  int getKnightCardsNum() const;
  //void addKnightCard();
  std::map<ResourceType, int> getResourcesList();
  void givePlayersResources(const Board &board, int diceNum);
  void addAndSubMultyResources(const std::vector<std::pair<ResourceType, int>> &resources);
  void placeSettelemnt(std::vector<ResourceType> resourseTypes, std::vector<int> itemNum, const Board &board);
  void placeCity(std::vector<ResourceType> resourseTypes, std::vector<int> itemNum, const Board &board);
  void addPoint(int num);
  void placeRoad(std::vector<ResourceType> resourseTypes, std::vector<int> itemNum, const Board &board);
  void rollDice(const Board &board, Catan *catan, int diceNum);
  void PlayerRolled7(Catan *catan, int diceNum);
  void endTurn(Catan *catan);
  void trade(Player &other, ResourceType give, ResourceType recieve, int giveAmount, int receiveAmount);
  void trade(Player &other, CardType give, CardType recieve);
  void printPlayerStatus();
  bool has2roads(Vertex *v);
  bool isPlayerTurn() const;
  int SettlmenCount();
  int cityCount();
  int roadCount();
  const char *toString(CardType type);
  void printDevelopmentCardsMap();
};

#endif // PLAYER_HPP
