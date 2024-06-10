//id:324207935 email:shbabkoff123@gmail.com
#include "Player.hpp"
#include "Board.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <random>
#include "Catan.hpp"
using namespace std;

Player::Player(string name, int index) : name_(name), playerIndex_(index)
{
    // Initialize each card type with a count of 0
    for (int i = 0; i < 5; ++i)
    {
        developmentCardsMap_[static_cast<CardType>(i)] = 0;
    }
}
Player::~Player() {}
void Player::addAndRemoveCard(CardType type, int num)
{
    developmentCardsMap_[type] += num;
}
map<CardType, int> Player::getDevelopmentCardsMap()
{
    return developmentCardsMap_;
}
int Player::getCardNum(CardType type)
{
    return developmentCardsMap_[type];
}
string Player::getPlayerName() const { return name_; }
vector<Vertex *> Player::getPlayerVerticesList() const { return verticesList_; }
vector<Edge *> Player::getPlayerEdgesList() const { return edgesList_; }
int Player::getPlayerPoints() const { return points_; }
void Player::addAndSubResource(ResourceType resource, int num)
{
    resourceCards_[resource] += num;
}
int Player::getResorceCount(ResourceType resource)
{
    return resourceCards_[resource];
}
map<ResourceType, int> Player::getResourcesList()
{
    return resourceCards_;
}
void Player::addPoint(int num)
{
    points_ += num;
}
int Player::SettlmenCount()
{
    int ans = 0;
    for (Vertex *v : verticesList_)
    {
        if (v->getPopulatedEntity() == PopulatedEntity::SETTLEMENT)
        {
            ans++;
        }
    }
    return ans;
}
int Player::cityCount()
{
    int ans = 0;
    for (Vertex *v : verticesList_)
    {
        if (v->getPopulatedEntity() == PopulatedEntity::CITY)
        {
            ans++;
        }
    }
    return ans;
}
int Player::roadCount()
{
    return edgesList_.size();
}
const char *Player::toString(CardType type)
{
    switch (type)
    {
    case CardType::KNIGHT:
        return "Knight";
    case CardType::VICTORY:
        return "Victory";
    case CardType::YEAR_OF_PLENTY:
        return "Year of Plenty";
    case CardType::MONOPOLY:
        return "Monopoly";
    case CardType::ROADS:
        return "Roads";
    default:
        return "Unknown Card Type";
    }
}
void Player::printDevelopmentCardsMap()
{
    for (const auto &pair : developmentCardsMap_)
    {
        cout << toString(pair.first) << ": " << pair.second << " cards\n";
    }
}
bool Player::isPlayerTurn() const { return isPlayerTurn_; }
// gpoing throgh the hexigons vertices list and if there is a mutual vertex-> return it
Vertex *findMutualVertex(const Hexigon &h1, const Hexigon &h2, const Hexigon &h3)
{
    for (Vertex *v1 : h1.getVerticesList())
    {
        for (Vertex *v2 : h2.getVerticesList())
        {
            for (Vertex *v3 : h3.getVerticesList())
            {
                if (v1 == v2 && v2 == v3 && v1 == v3)
                {
                    return v1; // Found the mutual vertex
                }
            }
        }
    }
    return nullptr; // No mutual vertex found
}
// going throgh the hexigons list and check if there is an hexigon with the d=samr number and resource
Hexigon *findHexigon(const vector<Hexigon *> &hexigonList, ResourceType resourceType, int itemNum)
{
    for (Hexigon *h1 : hexigonList)
    {
        if (h1->getNumber() == itemNum && h1->getType() == resourceType)
        {
            return h1;
        }
    }
    return nullptr;
}
// going  through the player roads and check if there is 2 roads connect that he owns
bool Player::has2roads(Vertex *v)
{
    for (Edge *e : edgesList_)
    {
        if ((e->getV1() == v || e->getV2() == v) && e->getEdgeOwner() == this)
        {
            Vertex *tmpVertex = e->getOtherVertex(v);
            if (tmpVertex)
            {
                for (Edge *e2 : edgesList_)
                {
                    if ((e2->getV1() == tmpVertex || e2->getV2() == tmpVertex) && e2->getEdgeOwner() == this)
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
// checking if vertex has already on the other side of some edge he connected to a vertex
bool hasNeighborSettlement(Vertex *v, Hexigon *h1, Hexigon *h2, Hexigon *h3)
{
    if (!v || !h1 || !h2 || !h3)
    {
        throw invalid_argument("Null pointer passed to hasNeighborSettlement");
    }

    for (Edge *edge : h1->getEdgesList())
    {
        if (!edge)
        {
            cerr << "Null edge found in h1" << endl;
            continue;
        }
        Vertex *other = edge->getOtherVertex(v);
        if (other && other->getPopulatedEntity() != PopulatedEntity::NONE)
        {
            return true;
        }
    }
    for (Edge *edge : h2->getEdgesList())
    {
        if (!edge)
        {
            cerr << "Null edge found in h2" << endl;
            continue;
        }
        Vertex *other = edge->getOtherVertex(v);
        if (other && other->getPopulatedEntity() != PopulatedEntity::NONE)
        {
            return true;
        }
    }
    for (Edge *edge : h3->getEdgesList())
    {
        if (!edge)
        {
            cerr << "Null edge found in h3" << endl;
            continue;
        }
        Vertex *other = edge->getOtherVertex(v);
        if (other && other->getPopulatedEntity() != PopulatedEntity::NONE)
        {
            return true;
        }
    }

    return false;
}

void Player::placeSettelemnt(vector<ResourceType> resourceTypes, vector<int> itemNum, const Board &board)
{
    // if its not the beggining of the game check if the player has all the resource that needed
    if (this->verticesList_.size() > 1 &&
        (resourceCards_[ResourceType::LUMBER] == 0 ||
         resourceCards_[ResourceType::BRICK] == 0 ||
         resourceCards_[ResourceType::GRAIN] == 0 ||
         resourceCards_[ResourceType::WOOL] == 0))
    {
        throw runtime_error("Error: player does not have the right resources");
    }
    // finding the 3 hexigons with the helper function findHexigon
    Hexigon *h1 = findHexigon(board.getHexigonsList(), resourceTypes[0], itemNum[0]);
    Hexigon *h2 = findHexigon(board.getHexigonsList(), resourceTypes[1], itemNum[1]);
    Hexigon *h3 = findHexigon(board.getHexigonsList(), resourceTypes[2], itemNum[2]);

    if (h1 == nullptr || h2 == nullptr || h3 == nullptr)
    {
        throw runtime_error("Error: One or more hexigons not found");
    }
    // finding the mutual vertex by eith the helper function findMutualVertex
    Vertex *mutualVertex = findMutualVertex(*h1, *h2, *h3);
    if (mutualVertex == nullptr)
    {
        throw runtime_error("Error: No mutual vertex found");
    }
    // checking if the wanted vertex has a neighbor vertex that sombody own
    if (hasNeighborSettlement(mutualVertex, h1, h2, h3))
    {
        throw runtime_error("Error: Vertex has neighbor settlement");
    }
    // if its not the beggining of the game, ceck if the vertex has 2 roads connected that the player own
    if (this->verticesList_.size() > 1 && !(has2roads(mutualVertex)))
    {
        throw runtime_error("Error: Vertex does not have 2 roads");
    }
    // here we know the vertex is valid and a settelment is going to be built
    // if its not the beggining of the game remove the resources from the player map
    if (this->verticesList_.size() > 1)
    {
        resourceCards_[ResourceType::LUMBER]--;
        resourceCards_[ResourceType::BRICK]--;
        resourceCards_[ResourceType::GRAIN]--;
        resourceCards_[ResourceType::WOOL]--;
    }
    else
    {
        // if it is the beggining of the game, give the player 1 card from each resource the vertex connect
        for (ResourceType t : resourceTypes)
        {
            if (t != ResourceType::SEA)
            {
                resourceCards_[t]++;
            }
        }
    }

    mutualVertex->setPopulatedEntity(PopulatedEntity::SETTLEMENT); // set the vertex as settlement
    mutualVertex->setVertexOwner(this);                            // set the vertex owner to be the player
    this->addVertex(mutualVertex);                                 // add vertex to the player vertices list
    this->points_++;                                               // add 1 point to the player

    cout << "Settlement placed at vertex: " << mutualVertex->getId() << endl;
}
bool Player::hasRequiredResources(const vector<ResourceType> &resources)
{
    for (auto &resource : resources)
    {
        if (getResorceCount(resource) == 0)
            return false;
    }
    return true;
}
// finding mutual edge between 2 hexigons
Edge *findMutualEdge(Hexigon *h1, Hexigon *h2)
{
    for (Edge *e1 : h1->getEdgesList())
    {
        for (Edge *e2 : h2->getEdgesList())
        {
            if ((e1->getV1() == e2->getV1() && e1->getV2() == e2->getV2()) ||
                (e1->getV1() == e2->getV2() && e1->getV2() == e2->getV1()))
            {
                return e1;
            }
        }
    }
    return nullptr;
}

void Player::placeRoad(vector<ResourceType> resourceTypes, vector<int> itemNum, const Board &board)
{
    //insure its the player turn
     if (!this->isPlayerTurn_)
    {
        throw invalid_argument("not player turn");
    }
    // if its not the beggining of the game check if the player have the right resources
    if ((!hasRequiredResources({ResourceType::LUMBER, ResourceType::BRICK}) && this->edgesList_.size() > 1))
    {

        throw invalid_argument("Error: Insufficient resources to build a road");
    }

    Hexigon *h1 = findHexigon(board.getHexigonsList(), resourceTypes[0], itemNum[0]);
    Hexigon *h2 = findHexigon(board.getHexigonsList(), resourceTypes[1], itemNum[1]);
    if (h1 == nullptr || h2 == nullptr)
    {

        throw invalid_argument("Error: One or both hexigons not found.");
    }
    //finding the wanted edge to build on
    Edge *edge = findMutualEdge(h1, h2);
    if (edge == nullptr || edge->getV1() == nullptr || edge->getV2() == nullptr)
    {

        throw invalid_argument("Error: Invalid edge details.");
    }

    if (edge->getEdgeOwner() != nullptr)
    {
        //check if the edge has a road already
        throw invalid_argument("Error: Edge already owned.");
    }
    if (this->edgesList_.size() < 2)
    {
        //if the beginingg of the game only chach if it connect to a vertex the player own
        if (edge->getV1()->getVertexOwner() == this || edge->getV2()->getVertexOwner() == this)
        {
            edge->setEdgeOwner(this);//st the player as the edge owner
            this->addEdge(edge);//adding the edge to the player edge list
            cout << "Road built by " << this->getPlayerName() << " at edge: (" << edge->getV1()->getId() << "," << edge->getV2()->getId() << ")" << endl;
            return;
        }
    }

    // if its not a beggining Check connection to existing roads
    bool isConnected = false;
    for (Edge *e : this->edgesList_)
    {
        if (e->getV1() == edge->getV1() || e->getV1() == edge->getV2() || e->getV2() == edge->getV1() || e->getV2() == edge->getV2())
        {
            isConnected = true;
            break;
        }
    }

    if (!isConnected)
    {

        throw invalid_argument("Error: Road must connect to an existing road.");
    }

    // Set the owner of the edge and update resources
    edge->setEdgeOwner(this);
    this->addEdge(edge);
    //remove the resources
    resourceCards_[ResourceType::LUMBER]--;
    resourceCards_[ResourceType::BRICK]--;
    cout << "Road built by " << this->getPlayerName() << " at edge: (" << edge->getV1()->getId() << "," << edge->getV2()->getId() << ")" << endl;
}
void Player::trade(Player &other, CardType give, CardType recieve)
{
    //insure its the player turn
    if (!this->isPlayerTurn_)
    {
        throw invalid_argument("not player turn");
    }
    //insure the player doesnt trade with himself
    if (this->name_ == other.getPlayerName())
    {
        throw invalid_argument("player cant trade with hinself");
    }
    //insure both players has the wanted cards
    if (this->developmentCardsMap_[give] < 1 || other.getDevelopmentCardsMap()[recieve] < 1)
    {
        throw invalid_argument("one of the players dont have the wanted card");
    }
    //adding and removing the cards from each other 
    this->addAndRemoveCard(give, -1);
    this->addAndRemoveCard(recieve, 1);
    other.addAndRemoveCard(give, 1);
    other.addAndRemoveCard(recieve, -1);
    //in case a knight is traded
    if (give == CardType::KNIGHT && !(recieve == CardType::KNIGHT))
    {

        if (this->getDevelopmentCardsMap()[give] == 2)//means before he had 3
        {

            this->addPoint(-2);
        }
        if (other.getDevelopmentCardsMap()[give] == 3)//means he needs to get 2 points
        {
            other.addPoint(2);
        }
    }
    if (recieve == CardType::KNIGHT && !(give == CardType::KNIGHT))
    {

        if (this->getDevelopmentCardsMap()[recieve] == 3)//means he needs to get 2 points
        {
            this->addPoint(2);
        }
        if (other.getDevelopmentCardsMap()[recieve] == 2)//means he had 3
        {

            other.addPoint(-2);
        }
    }

    cout << "trade ended succesfully!" << endl;
}

int Player::totalResources() const
{
    int total = 0;
    for (const auto &resourcePair : resourceCards_)
    {
        total += resourcePair.second; // resourcePair.second is the count of each resource type
    }
    return total;
}
void Player::rollDice(const Board &board, Catan *catan, int diceNum)
{
    //insuring its the player turn
    if (!isPlayerTurn_)
    {
        throw invalid_argument("not player turn...");
    }
    //special case when rolling 7
    if (diceNum == 7)
    {
        cout << name_ << " rolled 7" << endl;
        PlayerRolled7(catan, diceNum);
        return;
    }
    //giving all the players that have a settlement/city near the number
    givePlayersResources(board, diceNum);
    cout << name_ << " rolls the dice: " << diceNum << endl;
}
//helper function for case the player rolled 7:
//if a player has 7 cards or more he needs to remove half of his cards
void Player::PlayerRolled7(Catan *catan, int diceNum)
{

    for (Player *p : catan->getPlayersList())
    {
        int totalResources = p->totalResources();
        if (totalResources >= 7)//if he has 7 or more cards
        {
            int resourcesToDiscard = totalResources / 2; // Calculate half the resources
            // Iterate over resources and try to discard them
            for (auto &resourcePair : p->getResourcesList())
            {
                while (resourcesToDiscard > 0 && resourcePair.second > 0)
                {
                    p->addAndSubResource(resourcePair.first, -1);
                    resourcePair.second--; // Decrement the count of the current resource
                    resourcesToDiscard--;  // Decrement the number of resources still to discard
                }
                if (resourcesToDiscard <= 0)
                {
                    break; // Exit if we have discarded enough resources
                }
            }
        }
    }
}

//helper function that gives the players the resourcr if they have something built near the number
void Player::givePlayersResources(const Board &board, int diceNum)
{
    //going throgh all hexigons
    for (Hexigon *h : board.getHexigonsList())
    {
        //finding the hexigon with the same number as the diceNum
        if (h->getNumber() == diceNum)
        {
            //going throgh the vertices of the hexigon
            for (Vertex *v : h->getVerticesList())
            {
                if (v->getVertexOwner() != NULL)
                {
                    //for settlement add 1 for the resource and for city 2
                    if (v->getPopulatedEntity() == PopulatedEntity::SETTLEMENT)
                    {
                        v->getVertexOwner()->addAndSubResource(h->getType(), 1);
                    }
                    else if (v->getPopulatedEntity() == PopulatedEntity::CITY)
                    {
                        v->getVertexOwner()->addAndSubResource(h->getType(), 2);
                    }
                }
            }
        }
    }
}

void Player::endTurn(Catan *catan)
{
    //calling catan end turn function (as in catan i have the players list)
    catan->endTurn();
    cout << name_ << " end his turn" << endl;
    if (this->points_ == 10)
    {
        cout << this->name_ << " has 10 and wins the game!!!!" << endl;
    }
}
void Player::placeCity(vector<ResourceType> resourseTypes, vector<int> itemNum, const Board &board)
{
     //insuring its the player turn
    if (!isPlayerTurn_)
    {
        throw invalid_argument("not player turn...");
    }
    //insuring we are not in the beggining of the game
    if (this->verticesList_.size() < 2)
    {

        throw invalid_argument("Error: player can not build city before he has at list 2 settelments...");
    }
//check if the player has enoth resources
    if (resourceCards_[ResourceType::ORE] < 3 ||
        resourceCards_[ResourceType::GRAIN] < 2)
    {
        throw invalid_argument("Error: player does not have the right resources");
    }
//finding the hexigons
    Hexigon *h1 = findHexigon(board.getHexigonsList(), resourseTypes[0], itemNum[0]);
    Hexigon *h2 = findHexigon(board.getHexigonsList(), resourseTypes[1], itemNum[1]);
    Hexigon *h3 = findHexigon(board.getHexigonsList(), resourseTypes[2], itemNum[2]);

    if (h1 == nullptr || h2 == nullptr || h3 == nullptr)
    {
        throw invalid_argument("Error: One or more hexigons not found.");
    }
//finding mutual vertex
    Vertex *mutualVertex = findMutualVertex(*h1, *h2, *h3);

    if (mutualVertex == nullptr)
    {
        throw invalid_argument("Error: No mutual vertex found.");
    }
    //insuring you own this vertex
    if (mutualVertex->getVertexOwner() != this)
    {
        throw invalid_argument("Error:no settelment you own here");
    }
    //insuring you have a settlement there
    if (mutualVertex->getPopulatedEntity() != PopulatedEntity::SETTLEMENT)
    {
        throw invalid_argument("you already have a city here...");
    }
    mutualVertex->setPopulatedEntity(PopulatedEntity::CITY);//set vertex as city
    resourceCards_[ResourceType::ORE] -= 3;
    resourceCards_[ResourceType::GRAIN] -= 2;//remove the resources
    this->points_++;//adding 1 point to the player
    cout << "city placed at vertex: " << mutualVertex->getId() << endl;
}
//trade with resources
void Player::trade(Player &other, ResourceType give, ResourceType recieve, int giveAmount, int receiveAmount)
{
     //insure its the player turn
    if (!this->isPlayerTurn_)
    {
        throw invalid_argument("not player turn");
    }
    //insuring player doesnt trade with himself
    if (this->name_ == other.name_)
    {
        throw invalid_argument("player cant trade with himself");
    }
    //insuring both players has the needed resources
    if (this->resourceCards_[give] < giveAmount || other.getResourcesList()[recieve] < receiveAmount)
    {
        throw invalid_argument("one of the players dont have the wanted resource");
    }
    //adding and removing the resources
    this->addAndSubResource(recieve, receiveAmount);
    this->addAndSubResource(give, -giveAmount);
    other.addAndSubResource(give, giveAmount);
    other.addAndSubResource(recieve, -receiveAmount);
}

void Player::addAndSubMultyResources(const vector<pair<ResourceType, int>> &resources)
{
    for (auto &resource : resources)
    {
        addAndSubResource(resource.first, resource.second);
    }
}
void Player::printPlayerStatus()
{
    cout << this->name_ << " resources: " << "brick: " << this->getResorceCount(ResourceType::BRICK);
    cout << " ore: " << this->getResorceCount(ResourceType::ORE);
    cout << " lumber: " << this->getResorceCount(ResourceType::LUMBER);
    cout << " grain: " << this->getResorceCount(ResourceType::GRAIN);
    cout << " wool: " << this->getResorceCount(ResourceType::WOOL);
    cout << " knight cards: " << developmentCardsMap_[CardType::KNIGHT] << endl;
    cout << "city: " << this->cityCount() << " settelment: " << this->SettlmenCount() << " road: " << this->roadCount() << endl;
}
string Player::playerStatusString()
{
    ostringstream ans;
    ans << this->name_ << " resources: " << "brick: " << this->getResorceCount(ResourceType::BRICK);
    ans << " ore: " << this->getResorceCount(ResourceType::ORE);
    ans << " lumber: " << this->getResorceCount(ResourceType::LUMBER);
    ans << " grain: " << this->getResorceCount(ResourceType::GRAIN);
    ans << " wool: " << this->getResorceCount(ResourceType::WOOL);
    ans << " knight cards: " << developmentCardsMap_[CardType::KNIGHT];
    ans << " city: " << this->cityCount() << " settelment: " << this->SettlmenCount() << " road: " << this->roadCount() << " points: " << this->getPlayerPoints();
    return ans.str();
}