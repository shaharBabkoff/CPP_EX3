#include "Board.hpp"
#include <iostream>
//#include "DevelopmentCard.hpp"

Board::Board() : vertices_(54, nullptr) // Initialize with 72 null pointers
{
    initializeVertices();
    initializHexigons();
// initializeDevelopmentCards();

}
// void Board::shuffleCards() {
//     std::shuffle(developmentCards_.begin(), developmentCards_.end(), rng);
// }
// DevelopmentCard* Board::getRandomCard() {
//     if (developmentCards_.empty()) {
//         std::cerr << "No cards available." << std::endl;
//         return nullptr;
//     }
//     // Generate a random index to select a card
//     std::uniform_int_distribution<size_t> dist(0, developmentCards_.size() - 1);
//     size_t index = dist(rng);
//     return developmentCards_[index].get();  // Return pointer to the card
// }
// void Board::initializeDevelopmentCards() {
//     // Create 3 Knight cards
//     for (int i = 0; i < 3; ++i) {
//         developmentCards_.push_back(std::make_unique<KnightCard>());
//     }

//     // Create 4 of each of the other types of cards
//     for (int i = 0; i < 4; ++i) {
//         developmentCards_.push_back(std::make_unique<RoadBuildingCard>());
//         developmentCards_.push_back(std::make_unique<VictoryCard>());
//         developmentCards_.push_back(std::make_unique<MonopolyCard>());
//         developmentCards_.push_back(std::make_unique<YearOfPlenty>());
//         // Add other cards similarly
//     }
// }
void Board::initializeVertices()
{
    for (int i = 0; i < 54; i++)
    {
        vertices_[i] = new Vertex(i);
    }

    // updateVertexNeighbers();
}

void Board::initializHexigons()
{
    hexigons_.push_back(new Hexigon(10, ResourceType::ORE, {0, 1, 9, 8, 7, 5}, &vertices_));
    hexigons_.push_back(new Hexigon(2, ResourceType::WOOL, {2, 3, 11, 10, 9, 1}, &vertices_));
    hexigons_.push_back(new Hexigon(9, ResourceType::LUMBER, {4, 6, 13, 12, 11, 3}, &vertices_));
    hexigons_.push_back(new Hexigon(12, ResourceType::GRAIN, {7, 8, 18, 17, 16, 14}, &vertices_));
    hexigons_.push_back(new Hexigon(6, ResourceType::BRICK, {9, 10, 20, 19, 18, 8}, &vertices_));
    hexigons_.push_back(new Hexigon(4, ResourceType::WOOL, {11, 12, 22, 21, 20, 10}, &vertices_));
    hexigons_.push_back(new Hexigon(10, ResourceType::BRICK, {13, 15, 24, 23, 22, 12}, &vertices_));
    hexigons_.push_back(new Hexigon(9, ResourceType::GRAIN, {16, 17, 29, 28, 27, 25}, &vertices_));
    hexigons_.push_back(new Hexigon(11, ResourceType::LUMBER, {18, 19, 31, 30, 29, 17}, &vertices_));
    hexigons_.push_back(new Hexigon(0, ResourceType::NONE, {20, 21, 33, 32, 31, 19}, &vertices_));
    hexigons_.push_back(new Hexigon(3, ResourceType::LUMBER, {22, 23, 35, 34, 33, 21}, &vertices_));
    hexigons_.push_back(new Hexigon(8, ResourceType::ORE, {24, 26, 37, 36, 35, 23}, &vertices_));
    hexigons_.push_back(new Hexigon(8, ResourceType::LUMBER, {29, 30, 40, 39, 38, 28}, &vertices_));
    hexigons_.push_back(new Hexigon(3, ResourceType::ORE, {31, 32, 42, 41, 40, 30}, &vertices_));
    hexigons_.push_back(new Hexigon(4, ResourceType::GRAIN, {33, 34, 44, 43, 42, 32}, &vertices_));
    hexigons_.push_back(new Hexigon(5, ResourceType::WOOL, {35, 36, 46, 45, 44, 34}, &vertices_));
    hexigons_.push_back(new Hexigon(5, ResourceType::BRICK, {40, 41, 49, 48, 47, 39}, &vertices_));
    hexigons_.push_back(new Hexigon(6, ResourceType::GRAIN, {42, 43, 51, 50, 49, 41}, &vertices_));
    hexigons_.push_back(new Hexigon(11, ResourceType::WOOL, {44, 45, 53, 52, 51, 43}, &vertices_));
    hexigons_.push_back(new Hexigon(1, ResourceType::SEA, {5, 0}, &vertices_));
    hexigons_.push_back(new Hexigon(2, ResourceType::SEA, {0, 1, 2}, &vertices_));
    hexigons_.push_back(new Hexigon(3, ResourceType::SEA, {2, 3, 4}, &vertices_));
    hexigons_.push_back(new Hexigon(4, ResourceType::SEA, {4, 6}, &vertices_));
    hexigons_.push_back(new Hexigon(5, ResourceType::SEA, {6, 13, 15}, &vertices_));
    hexigons_.push_back(new Hexigon(6, ResourceType::SEA, {15, 24, 26}, &vertices_));
    hexigons_.push_back(new Hexigon(7, ResourceType::SEA, {26, 37}, &vertices_));
    hexigons_.push_back(new Hexigon(8, ResourceType::SEA, {37, 36, 46}, &vertices_));
    hexigons_.push_back(new Hexigon(9, ResourceType::SEA, {46, 45, 53}, &vertices_));
    hexigons_.push_back(new Hexigon(10, ResourceType::SEA, {53, 52}, &vertices_));
    hexigons_.push_back(new Hexigon(11, ResourceType::SEA, {52, 51, 50}, &vertices_));
    hexigons_.push_back(new Hexigon(12, ResourceType::SEA, {50, 49, 48}, &vertices_));
    hexigons_.push_back(new Hexigon(13, ResourceType::SEA, {48, 47}, &vertices_));
    hexigons_.push_back(new Hexigon(14, ResourceType::SEA, {47, 39, 38}, &vertices_));
    hexigons_.push_back(new Hexigon(15, ResourceType::SEA, {38, 28, 27}, &vertices_));
    hexigons_.push_back(new Hexigon(16, ResourceType::SEA, {27, 25}, &vertices_));
    hexigons_.push_back(new Hexigon(17, ResourceType::SEA, {25, 16, 14}, &vertices_));
    hexigons_.push_back(new Hexigon(18, ResourceType::SEA, {14, 7, 5}, &vertices_));
}
void Board::printBoard()
{

    std::cout << "Board Layout:" << std::endl;
    for (const Hexigon *hex : hexigons_)
    {
        std::cout << "Hexigon Number: " << hex->getNumber() << ", Type: ";
        switch (hex->getType())
        {
        case ResourceType::LUMBER:
            std::cout << "LUMBER";
            break;
        case ResourceType::BRICK:
            std::cout << "BRICK";
            break;
        case ResourceType::WOOL:
            std::cout << "WOOL";
            break;
        case ResourceType::GRAIN:
            std::cout << "GRAIN";
            break;
        case ResourceType::ORE:
            std::cout << "ORE";
            break;
        case ResourceType::NONE:
            std::cout << "NONE";
            break;
        case ResourceType::SEA:
            std::cout << "SEA";
            break;
        default:
            std::cout << "UNKNOWN";
        }
        std::cout << std::endl;

        std::cout << "Vertices: ";
        for (const Vertex *vert : hex->getVerticesList())
        {
            std::cout << vert->getId() << " ";
        }
        std::cout << std::endl;
    }
}

Board::~Board()
{
    // Clean up dynamically allocated memory
    for (auto hex : hexigons_)
    {
        delete hex;
    }
    for (auto vert : vertices_)
    {
        delete vert;
    }
}