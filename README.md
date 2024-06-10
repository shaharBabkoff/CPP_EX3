# Project Description

## Game Rules
This project implements a computerized version of the board game X. The game includes a number of players (specify the number of players), each aiming to achieve goal Y (describe the goal). The game progresses in turns, where each player can perform actions A, B, and C in each turn (detail these actions).

## Class Hierarchy
The implementation includes the following classes:
- `Game`: This class is responsible for running the game, managing turns, and enforcing the rules.
- `Player`: This class represents a player in the game. It contains all attributes and properties of the player.
- `Board`: This class represents the game board and interactions on it.
- `Card`: An abstract class for the cards in the game, with derived classes such as `TreasureCard`, `MonsterCard`, etc.

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
