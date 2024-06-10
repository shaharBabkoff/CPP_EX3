# Project Description

## Game Rules
This project implements a computerized version of the board game catcn. The game includes 3 players, the winner is the first to get 10 points. The game progresses in turns, where each player roll dice and can perform actions like building(roads, settlements, citys) buying development cards and trade.

## Class Hierarchy
The implementation includes the following classes:
- `Board`: This class is responsible for the board structure. In this class all the hexigons and vertices are initialized.
The board contain 37 hexigons and 54 vertices
- `Hexigon`: Each hexigon is comprised of 6 vertices and 6 edges. Also he has an id number and a resource type
 - `Vertex`: Each vertex has a uniqe id, a player who own him and a pupulated entity 
- `Catan`: This class represents a player in the game. It contains all attributes and properties of the player.
- `Edge`: This class represents the game board and interactions on it.


- `Player` :
  
## Libraries Used
The project utilizes standard C++ libraries such as `<iostream>`, `<vector>`, `<map>`, and `<algorithm>` for input/output handling, list and map management, and data manipulation.

## Methods Implemented
Below is a description of several key methods in the project:
- `void Player::move(int x, int y)`: Moves the player to a new position on the game board, specified by coordinates x and y.
- `void Game::start()`: Initiates a new game session, setting up the board and distributing initial resources or cards to players.
- `void Board::update()`: Updates the state of the board with each turn, checking for win conditions and updating player positions.
- `bool Player::checkResources()`: Checks if the player has the necessary resources to perform a particular action.

## Running the Game
To start the game, compile the source files and run the executable. Ensure that all dependencies are properly configured in your development environment.

## Contributions
Feel free to fork this project and contribute to its development. Pull requests are welcome.

## License
This project is licensed under the MIT License - see the LICENSE file for details.
