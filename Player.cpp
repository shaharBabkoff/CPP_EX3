#include "Player.hpp"
#include "Board.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include "Catan.hpp"
using namespace std;

Player::~Player()
{
    // cout << "Player destructor called for " << name_ << endl;
}

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

Hexigon *findHexigon(const std::vector<Hexigon *> &hexigonList, ResourceType resourceType, int itemNum)
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

bool hasNeighborSettlement(Vertex *v, Hexigon *h1, Hexigon *h2, Hexigon *h3)
{
    if (!v || !h1 || !h2 || !h3)
    {
        std::cerr << "Null pointer passed to hasNeighborSettlement" << std::endl;
        return false; // Ensure none of the pointers are null
    }

    // Debugging information
    // std::cerr << "Checking hexigon h1" << std::endl;
    for (Edge *edge : h1->getEdgesList())
    {
        if (!edge)
        {
            std::cerr << "Null edge found in h1" << std::endl;
            continue;
        }
        Vertex *other = edge->getOtherVertex(v);
        if (other && other->getPopulatedEntity() != PopulatedEntity::NONE)
        {
            return true;
        }
    }

    // std::cerr << "Checking hexigon h2" << std::endl;
    for (Edge *edge : h2->getEdgesList())
    {
        if (!edge)
        {
            std::cerr << "Null edge found in h2" << std::endl;
            continue;
        }
        Vertex *other = edge->getOtherVertex(v);
        if (other && other->getPopulatedEntity() != PopulatedEntity::NONE)
        {
            return true;
        }
    }

    // std::cerr << "Checking hexigon h3" << std::endl;
    for (Edge *edge : h3->getEdgesList())
    {
        if (!edge)
        {
            std::cerr << "Null edge found in h3" << std::endl;
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

void Player::placeSettelemnt(vector<ResourceType> resourseTypes, vector<int> itemNum, Board *board)
{
    if (this->verticesList_.size() > 2 &&
        (resourceCards_[ResourceType::LUMBER] == 0 ||
         resourceCards_[ResourceType::BRICK] == 0 ||
         resourceCards_[ResourceType::GRAIN] == 0 ||
         resourceCards_[ResourceType::WOOL] == 0))
    {
        cerr << "Error: player does not have the right resources" << endl;
        return;
    }

    Hexigon *h1 = findHexigon(board->getHexigonsList(), resourseTypes[0], itemNum[0]);
    Hexigon *h2 = findHexigon(board->getHexigonsList(), resourseTypes[1], itemNum[1]);
    Hexigon *h3 = findHexigon(board->getHexigonsList(), resourseTypes[2], itemNum[2]);

    if (h1 == nullptr || h2 == nullptr || h3 == nullptr)
    {
        std::cerr << "Error: One or more hexigons not found." << std::endl;
        return;
    }

    Vertex *mutualVertex = findMutualVertex(*h1, *h2, *h3);

    if (mutualVertex == nullptr)
    {
        std::cerr << "Error: No mutual vertex found." << std::endl;
        return;
    }

    if (hasNeighborSettlement(mutualVertex, h1, h2, h3))
    {
        cerr << "vertex has neighbor settlement" << endl;
        return;
    }

    if (this->verticesList_.size() > 2 && !(has2roads(mutualVertex)))
    {
        cerr << "vertex does not have 2 roads" << endl;
        return;
    }

    mutualVertex->setPopulatedEntity(PopulatedEntity::SETTLEMENT);
    mutualVertex->setVertexOwner(this);
    this->addVertex(mutualVertex);
    this->points_++;

    if (this->verticesList_.size() > 2)
    {
        resourceCards_[ResourceType::LUMBER]--;
        resourceCards_[ResourceType::BRICK]--;
        resourceCards_[ResourceType::GRAIN]--;
        resourceCards_[ResourceType::WOOL]--;
    }
    else
    {
        for (ResourceType t : resourseTypes)
        {
            if (t != ResourceType::SEA)
            {
                resourceCards_[t]++;
            }
        }
    }

    cout << "Settlement placed at vertex: " << mutualVertex->getId() << endl;
}
bool Player::hasRequiredResources(const std::vector<ResourceType> &resources)
{
    for (auto &resource : resources)
    {
        if (getResorceCount(resource) == 0)
            return false;
    }
    return true;
}
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

void Player::placeRoad(vector<ResourceType> resourceTypes, vector<int> itemNum, Board *board)
{
    // if (!isPlayerTurn_)
    // {
    //     cout << "Not " << this->name_ << "'s turn." << endl;
    //     return;
    // }

    if ((resourceCards_[ResourceType::LUMBER] == 0 || resourceCards_[ResourceType::BRICK] == 0) && this->edgesList_.size() > 1)
    {
        cerr << "Error: Insufficient resources to build a road." << endl;
        return;
    }

    Hexigon *h1 = findHexigon(board->getHexigonsList(), resourceTypes[0], itemNum[0]);
    Hexigon *h2 = findHexigon(board->getHexigonsList(), resourceTypes[1], itemNum[1]);
    if (h1 == nullptr || h2 == nullptr)
    {
        cerr << "Error: One or both hexigons not found." << endl;
        return;
    }

    Edge *edge = findMutualEdge(h1, h2);
    if (edge == nullptr || edge->getV1() == nullptr || edge->getV2() == nullptr)
    {
        cerr << "Error: Invalid edge details." << endl;
        return;
    }

    if (edge->getEdgeOwner() != nullptr)
    {
        cout << "Error: Edge already owned." << endl;
        return;
    }
    if (this->edgesList_.size() < 2)
    {
        if (edge->getV1()->getVertexOwner() == this || edge->getV2()->getVertexOwner() == this)
        {
            edge->setEdgeOwner(this);
            this->addEdge(edge);
            cout << "Road built by " << this->getPlayerName() << " at edge: (" << edge->getV1()->getId() << "," << edge->getV2()->getId() << ")" << endl;
            return;
        }
    }

    // Check connection to existing roads
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
        cout << "Error: Road must connect to an existing road." << endl;
        return;
    }

    // Set the owner of the edge and update resources
    edge->setEdgeOwner(this);
    this->addEdge(edge);
    resourceCards_[ResourceType::LUMBER]--;
    resourceCards_[ResourceType::BRICK]--;
    cout << "Road built by " << this->getPlayerName() << " at edge: (" << edge->getV1()->getId() << "," << edge->getV2()->getId() << ")" << endl;
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
void Player::rollDice(Board *board, Catan *catan)
{
    if (!isPlayerTurn_)
    {
        cerr << "not " << this->name_ << " turn" << endl;
        return;
    }
    std::random_device rd;
    // Choose a random number between 2 and 12
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(2, 12);
    int diceNum = distr(eng);
    ifPlayerRolled7(catan,diceNum);
    givePlayersResources(board, diceNum);
    std::cout << name_ << " rolls the dice: " << diceNum << std::endl;
}
void Player::ifPlayerRolled7(Catan* catan,int diceNum){
    if (diceNum == 7)
    {
        for (Player *p : catan->getPlayersList())
        {
            int totalResources = p->totalResources();
            if (totalResources >= 7)
            {
                int count = totalResources / 2;       // Number of resources to discard
                auto &resourceCards = resourceCards_; // Assuming getResourceCards() returns a reference to resourceCards_

                std::vector<ResourceType> resourcesToDiscard;
                for (const auto &resourcePair : resourceCards)
                {
                    for (int i = 0; i < resourcePair.second; ++i)
                    {
                        resourcesToDiscard.push_back(resourcePair.first);
                    }
                }

                std::random_shuffle(resourcesToDiscard.begin(), resourcesToDiscard.end()); // Randomize the resource order

                // Discard resources
                for (int i = 0; i < count && !resourcesToDiscard.empty(); ++i)
                {
                    ResourceType resourceType = resourcesToDiscard.back();
                    resourceCards[resourceType]--; // Decrease the resource count
                    resourcesToDiscard.pop_back(); // Remove from the discard list
                }
            }
        }
    }

}
void Player::givePlayersResources(Board *board, int diceNum)
{
    for (Hexigon *h : board->getHexigonsList())
    {
        if (h->getNumber() == diceNum)
        {
            for (Vertex *v : h->getVerticesList())
            {
                if (v->getVertexOwner() != NULL)
                {
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
void Player::rollDice(Board *board, int diceNum)
{
    if (!isPlayerTurn_)
    {
        // cout << this->isPlayerTurn_ << endl;
        cerr << "not " << this->name_ << " turn" << endl;
        return;
    }

    // Choose a random number between 2 and 12

    for (Hexigon *h : board->getHexigonsList())
    {
        if (h->getNumber() == diceNum)
        {
            for (Vertex *v : h->getVerticesList())
            {
                if (v->getVertexOwner() != NULL)
                {
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

    std::cout << name_ << " rolls the dice: " << diceNum << std::endl;
}
void Player::addAndSubMultyResources(const std::vector<std::pair<ResourceType, int>> &resources)
{
    for (auto &resource : resources)
    {
        addAndSubResource(resource.first, resource.second);
    }
}

void Player::endTurn(Catan *catan)
{
    catan->endTurn();
    cout << name_ << " end his turn" << endl;
    if (this->points_ == 10)
    {
        cout << this->name_ << " has 10 and wins the game!!!!" << endl;
    }
}
void Player::placeCity(std::vector<ResourceType> resourseTypes, std::vector<int> itemNum, Board *board)
{
    if (this->verticesList_.size() < 2)
    {
        cerr << "Error: player can not build city before he has at list 2 settelments..." << endl;
        return;
    }

    if (resourceCards_[ResourceType::ORE] < 3 ||
        resourceCards_[ResourceType::GRAIN] < 2)
    {
        cerr << "Error: player does not have the right resources" << endl;
        return;
    }

    Hexigon *h1 = findHexigon(board->getHexigonsList(), resourseTypes[0], itemNum[0]);
    Hexigon *h2 = findHexigon(board->getHexigonsList(), resourseTypes[1], itemNum[1]);
    Hexigon *h3 = findHexigon(board->getHexigonsList(), resourseTypes[2], itemNum[2]);

    if (h1 == nullptr || h2 == nullptr || h3 == nullptr)
    {
        std::cerr << "Error: One or more hexigons not found." << std::endl;
        return;
    }

    Vertex *mutualVertex = findMutualVertex(*h1, *h2, *h3);

    if (mutualVertex == nullptr)
    {
        std::cerr << "Error: No mutual vertex found." << std::endl;
        return;
    }
    if (mutualVertex->getVertexOwner() != this)
    {
        std::cerr << "Error:no settelment you own here" << std::endl;
        return;
    }
    if (mutualVertex->getPopulatedEntity() != PopulatedEntity::SETTLEMENT)
    {
        std::cerr << "you already have a city here..." << std::endl;
        return;
    }
    mutualVertex->setPopulatedEntity(PopulatedEntity::CITY);
    resourceCards_[ResourceType::ORE] -= 3;
    resourceCards_[ResourceType::GRAIN] -= 2;
    this->points_++;
    cout << "city placed at vertex: " << mutualVertex->getId() << endl;
}

void Player::trade(Player &other, const std::string &give, const std::string &receive, int giveAmount, int receiveAmount)
{
    std::cout << name_ << " trades " << giveAmount << " " << give << " with " << other.getPlayerName() << " for " << receiveAmount << " " << receive << "." << std::endl;
}

void Player::buyDevelopmentCard()
{
    std::cout << name_ << " buys a development card." << std::endl;
}

void Player::printPoints()
{
    std::cout << name_ << " has X points." << std::endl; // Replace X with actual point calculation
}
