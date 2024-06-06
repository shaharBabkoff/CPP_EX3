#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "Vertex.hpp"
// #include
class Edge;

class Board;
enum class ResourceType; // Forward declaration
class Catan;

// Include for ResourceType
// #include "Hexigon.hpp"

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
  int knightCards_ = 0;

public:
  Player(std::string name, int index) : name_(name), playerIndex_(index) {}
  Player() : name_("") {}
  ~Player(); // Destructor

  std::string getPlayerName() const { return name_; }
  std::vector<Vertex *> getPlayerVerticesList() { return verticesList_; }
  std::vector<Edge *> getPlayerEdgesList() { return edgesList_; }
  int getPlayerPoints() const { return points_; }
  void addAndSubResource(ResourceType resource, int num)
  {
    resourceCards_[resource] += num;
  }
  int getResorceCount(ResourceType resource)
  {
    return resourceCards_[resource];
  }
  int totalResources() const ;
  void addVertex(Vertex *v) { verticesList_.push_back(v); }
  void addEdge(Edge *e) { edgesList_.push_back(e); }
  void setPlayerTurn(bool turn) { isPlayerTurn_ = turn; }
  Edge *getValidEdge();
  bool hasRequiredResources(const std::vector<ResourceType> &resources);
  // void placeRoad(Edge* edge);
  int getKnightCardsNum()
  {
    return knightCards_;
  }
  void addKnightCard(){
    knightCards_++;
  }
  std::map<ResourceType, int>  getResourcesList(){
    return resourceCards_;
  }
  void givePlayersResources(Board *board, int diceNum);
  void addAndSubMultyResources(const std::vector<std::pair<ResourceType, int>> &resources);
  void placeSettelemnt(std::vector<ResourceType> resourseTypes, std::vector<int> itemNum, Board *board);
  void placeCity(std::vector<ResourceType> resourseTypes, std::vector<int> itemNum, Board *board);
  void addPoint(int num)
  {
    points_ += num;
  }
  void placeRoad(std::vector<ResourceType> resourseTypes, std::vector<int> itemNum, Board *board);
  void rollDice(Board *board,Catan *catan);
  void rollDice(Board *board, Catan *catan, int diceNum);
  void PlayerRolled7(Catan* catan,int diceNum);
  void endTurn(Catan *catan);
  void trade(Player &other, ResourceType give, ResourceType recieve, int giveAmount, int receiveAmount);
  void buyDevelopmentCard();
  void printPoints();
  void printPlayerStatus();
  bool has2roads(Vertex *v);
  bool isPlayerTurn() const { return isPlayerTurn_; }
  int SettlmenCount(){
    int ans =0;
    for(Vertex* v:verticesList_){
      if(v->getPopulatedEntity()==PopulatedEntity::SETTLEMENT){
        ans++;
      }
    }
    return ans;
  }
  int cityCount(){
    int ans =0;
    for(Vertex* v:verticesList_){
      if(v->getPopulatedEntity()==PopulatedEntity::CITY){
        ans++;
      }
    }
    return ans;
  }
  int roadCount(){
    return edgesList_.size();
  }
  
};

#endif // PLAYER_HPP
