id:324207935
email: shbabkoff123@gmail.com
---
# Catan Game Project
---
## Game Rules
This project implements a computerized version of the board game Catan. The game includes 3 players, with the winner being the first to reach 10 points. The game progresses in turns, where each player can roll dice and perform actions such as building (roads, settlements, cities), buying development cards, and trading.

## Class Hierarchy
The implementation includes the following classes:
- **`Board`**: Responsible for the board structure. All hexagons and vertices are initialized in this class. The board contains 37 hexagons and 54 vertices.
- The board also includes sea hexagons that surround the hexagons with resources. This design requires that each time a player wants to build a city/settlement, they need to enter 3 hexagons, even if the desired vertex is on an edge next to the sea.
- **`Catan`**: Represents the actual game. Holds the player list and is responsible for tracking the players' turns.
- **`Hexigon`**: Each hexagon is comprised of 6 vertices and 6 edges. It has an ID number and a resource type.
- **`Vertex`**: Each vertex has a unique ID, a player who owns it, and a populated entity. Players can build a settlement/city on a vertex according to the conditions.
- **`Edge`**: Represents an edge on the board where a player can build a road. Each edge is comprised of 2 vertices.
- **`Player`**: Represents a player in the game. Contains all attributes and properties of the player.

## Development Cards
Development cards provide players with different capabilities or advantages when activated. Each card type inherits from the abstract `DevelopmentCard` class, which provides the base structure and functionality common to all cards.

### `DevelopmentCard` (Abstract Base Class)
- **Attributes**:
  - `isBought_`: Boolean flag indicating whether the card has been purchased.
- **Methods**:
  - `setAsBought(bool val)`: Sets the card as bought.
  - `activate(Player *player)`: Pure virtual function to activate the card. Specific behavior is implemented in derived classes.
  - `getIfBought()`: Returns whether the card has been purchased.
  - `activateFirstCheck(Player *player)`: Performs initial checks before card activation (e.g., if it is the player's turn).
  - `activateEnd(Player *player)`: Concludes the activation process with cleanup or final steps.

### `RoadBuildingCard`
- Allows a player to build two roads at no resource cost.
- **Method**:
  - `activate(Player *player)`: Activates the card and gives the player 2 lumbers and 2 bricks

### `KnightCard`
- Represents a knight which a player that holds 3 knight cards gets 2 points
- knight card doesnt have activate method so it has an empty implementation for the activate function

### `VictoryCard`
- Grants an additional victory point to the player.
- **Method**:
  - `activate(Player *player)`: Adds a victory point to the player's score.

### `MonopolyCard`
- Allows a player to declare one resource type and take all of that resource from other players.
in oreder to activate the card the player needs first to set the wanted resource
- **Attributes**:
  - `resource_`: Specifies the resource type to be monopolized.
  - `playersList_`: List of players in the game to affect.
- **Methods**:
  - `setResource(ResourceType resource)`: Sets the resource type for the monopoly.
  - `activate(Player *player)`: Removes the specified resource from all other players and adds it to the activator’s resources.

### `YearOfPlenty`
- Allows a player to choose two resources to add to their inventory.
- in oreder to activate the card the player needs first to set the wanted resourcses
- **Attributes**:
  - `resource1_`: The first resource type chosen.
  - `resource2_`: The second resource type chosen.
- **Methods**:
  - `activate(Player *player)`: Adds the chosen resources to the player’s inventory.
  - `setResources(ResourceType resource1, ResourceType resource2)`: Sets the resources that the player will receive.

## trade development cards
In catan i initilze all the development cards: 3 knight and 4 from all the other types
if a player want to get a development card he use getDevelopmentCard function (in catan)
A card can be traded only if the player hasnt activate it yet.
Accept knight card which doesnt have activate method

---
