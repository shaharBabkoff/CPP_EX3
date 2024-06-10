//id:324207935 email:shbabkoff123@gmail.com
#include "Catan.hpp"
#include <iostream>
using namespace std;

// Constructor for the Catan game which initializes the game with three players.
// It sets up the game board, initializes development cards, and sets the first player's turn.
Catan::Catan(Player *p1, Player *p2, Player *p3)
    : board_(),                 // Initializes the game board
      playersList_{p1, p2, p3}, // Initializes the list of players participating in the game
      currentPlayerIndex_(1)    // Sets the first player index to 1 (assuming players are indexed 1, 2, 3)
{
    initialDevelopmentCards();  // Calls method to populate the initial set of development cards
    currentPlayerIndex_ = 1;    // Redundant setting of currentPlayerIndex_, consider removing
    playersList_[0]->setPlayerTurn(true); // Sets the turn to true for the first player
}

// Destructor for Catan, currently empty as smart pointers are handling most of the cleanup.
Catan::~Catan() {
    for (auto card : developmentCards_) {
        delete card;  // Free each dynamically allocated card
    }
    developmentCards_.clear();  // Clear the vector just to clean up
}

// Returns a list of players participating in the game.
vector<Player *> Catan::getPlayersList() const {
    return playersList_;
}

// Returns the index of the current player.
int Catan::getCurrentPlayerIndex() const {
    return currentPlayerIndex_;
}

// Sets the index of the current player.
void Catan::setCurrentIndex(int index) {
    currentPlayerIndex_ = index;
}

// Returns a reference to the game board.
Board &Catan::getBoard() {
    return board_;
}

// Determines and returns the name of the player who has won the game, or returns a message if no one has won yet.
string Catan::printWinner() {
    for (Player *p : playersList_) {
        if (p->getPlayerPoints() >= 10) {
            return p->getPlayerName(); // Returns the winning player's name if points are 10 or more
        }
    }
    return "no player has 10 points"; // No player has reached the winning criteria
}

// Prints the current status of each player in the game.
void Catan::printPlayersStatus() {
    for (Player *p : playersList_) {
        p->printPlayerStatus();
    }
}

// Ends the current player's turn and passes the turn to the next player.
void Catan::endTurn() {
    int nextIndex = (currentPlayerIndex_ % 3) + 1; // Cycles through player indices 1, 2, 3
    currentPlayerIndex_ = nextIndex;

    // Updates each player's turn status.
    for (int i = 0; i < 3; ++i) {
        playersList_[i]->setPlayerTurn(i + 1 == nextIndex);
    }
}
// Initializes the development cards at the beginning of the game.
void Catan::initialDevelopmentCards()
{
    for (int i = 0; i < 3; i++)
    {
        developmentCards_.push_back(new KnightCard());
    }
    for (int i = 0; i < 4; i++)
    {
        developmentCards_.push_back(new VictoryCard());
    }
    for (int i = 0; i < 4; i++)
    {

        developmentCards_.push_back(new YearOfPlenty());
    }
    for (int i = 0; i < 4; i++)
    {

        developmentCards_.push_back(new MonopolyCard(playersList_));
    }
    for (int i = 0; i < 4; i++)
    {

        developmentCards_.push_back(new RoadBuildingCard());
    }
}
// Retrieves a development card of a specified type for a player, handling game logic and exceptions.
DevelopmentCard *Catan::getDevelopmentCard(CardType type, Player &player) const
{
    if (!player.isPlayerTurn())
    {
        throw std::invalid_argument("not player turn");//insure its the player turn
    }
    if (!player.hasRequiredResources({ResourceType::ORE, ResourceType::GRAIN, ResourceType::WOOL}))
    {

        throw std::invalid_argument("Player does not have the right resources");//insure the player has the needed resource
    }
    int startIndex = 0, endIndex = 0;

    switch (type)
    {
    case CardType::KNIGHT:
        startIndex = 0;
        endIndex = 3; // Exclusive, so actual last index is 2
        break;
    case CardType::VICTORY:
        startIndex = 3;
        endIndex = 7; // Exclusive, so actual last index is 6
        break;
    case CardType::YEAR_OF_PLENTY:
        startIndex = 7;
        endIndex = 11; // Exclusive, so actual last index is 10
        break;
    case CardType::MONOPOLY:
        startIndex = 11;
        endIndex = 15; // Exclusive, so actual last index is 14
        break;
    case CardType::ROADS:
        startIndex = 15;
        endIndex = 19; // Exclusive, so actual last index is 18
        break;
    default:
        return nullptr; // Return null if card type is unknown or not handled
    }

    for (int i = startIndex; i < endIndex; i++)
    {
        if (!developmentCards_[i]->getIfBought())
        {
            player.addAndRemoveCard(type, 1);
            developmentCards_[i]->setAsBought(true);
            player.addAndSubMultyResources({{ResourceType::ORE, -1}, {ResourceType::GRAIN, -1}, {ResourceType::WOOL, -1}});
            //in my catan imlimentation, knight is a special card as you dont activate him
            //because of this i need to check this things here
            if (type == CardType::KNIGHT)
            {
                developmentCards_[i]->setAsBought(true);
                if (player.getDevelopmentCardsMap()[type] == 3)//if a player has 3 knight he gets 2 points
                {
                    player.addPoint(2);
                }
            }

            return developmentCards_[i];
        }
    }
    throw std::invalid_argument("no valid card from your type");
}
