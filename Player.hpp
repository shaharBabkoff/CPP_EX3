#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

//#include 
class Edge;
class Vertex;
class Board;
enum class ResourceType; // Forward declaration
class Catan;

// Include for ResourceType
//#include "Hexigon.hpp"

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
     int knightCards_ =0;

public:
    Player(std::string name,int index) : name_(name),playerIndex_(index) {}
    Player() : name_("") {}
    ~Player();// Destructor

    std::string getPlayerName() const { return name_; }
    std::vector<Vertex *> getPlayerVerticesList() { return verticesList_; }
    std::vector<Edge *> getPlayerEdgesList() { return edgesList_; }
    int getPlayerPoints() const { return points_; }
    void addAndSubResource(ResourceType resource,int num){
        resourceCards_[resource]+=num;
    }
    int getResorceCount(ResourceType resource){
      return resourceCards_[resource];
    }
    void addVertex(Vertex *v) { verticesList_.push_back(v); }
    void addEdge(Edge *e) { edgesList_.push_back(e); }
     void setPlayerTurn(bool turn) { isPlayerTurn_ = turn; }
    Edge* getValidEdge();
    bool hasRequiredResources(const std::vector<ResourceType>& resources) ;
   //void placeRoad(Edge* edge);
     int getKnightCardsNum(){
      return knightCards_;
     }
     void deductResources(const std::vector<std::pair<ResourceType, int>>& resources);
     void addKnightCard(){
      knightCards_++;
     }
   //bool canPlaceRoad(Edge* edge) ;
    void placeSettelemnt(std::vector<ResourceType> resourseTypes, std::vector<int> itemNum, Board *board);
    void placeCity(std::vector<ResourceType> resourseTypes, std::vector<int> itemNum, Board *board);
    void addPoint(int num){
      points_+=num;
    }
    void placeRoad(std::vector<ResourceType> resourseTypes, std::vector<int> itemNum, Board *board);
    void rollDice(Board *board);
    void rollDice(Board *board,int num);
    void endTurn(Catan *catan);
    void trade(Player &other, const std::string &give, const std::string &receive, int giveAmount, int receiveAmount);
    void buyDevelopmentCard();
    void printPoints();
    bool has2roads(Vertex *v);
      bool isPlayerTurn() const { return isPlayerTurn_; }
};

#endif // PLAYER_HPP
