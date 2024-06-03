CXX = g++
CXXFLAGS = -std=c++14 -Wall


# Define the target executable
TARGET = Demo

# Define the object files
OBJS = Board.o Catan.o DevelopmentCard.o Hexigon.o Player.o Vertex.o Edge.o Demo.o

# Default target to build the project
all: $(TARGET)

# Rule to link object files and create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile Board.cpp into Board.o
Board.o: Board.cpp Board.hpp Hexigon.hpp Vertex.hpp Edge.hpp DevelopmentCard.hpp
	$(CXX) $(CXXFLAGS) -c Board.cpp

# Rule to compile Catan.cpp into Catan.o
Catan.o: Catan.cpp Catan.hpp Player.hpp Board.hpp DevelopmentCard.hpp
	$(CXX) $(CXXFLAGS) -c Catan.cpp

# Rule to compile DevelopmentCard.cpp into DevelopmentCard.o
DevelopmentCard.o: DevelopmentCard.cpp DevelopmentCard.hpp Player.hpp
	$(CXX) $(CXXFLAGS) -c DevelopmentCard.cpp

# Rule to compile Hexigon.cpp into Hexigon.o
Hexigon.o: Hexigon.cpp Hexigon.hpp Vertex.hpp Edge.hpp
	$(CXX) $(CXXFLAGS) -c Hexigon.cpp

# Rule to compile Player.cpp into Player.o
Player.o: Player.cpp Player.hpp DevelopmentCard.hpp Edge.hpp
	$(CXX) $(CXXFLAGS) -c Player.cpp

# Rule to compile Vertex.cpp into Vertex.o
Vertex.o: Vertex.cpp Vertex.hpp Hexigon.hpp Edge.hpp
	$(CXX) $(CXXFLAGS) -c Vertex.cpp

# Rule to compile Edge.cpp into Edge.o
Edge.o: Edge.cpp Edge.hpp Vertex.hpp Hexigon.hpp
	$(CXX) $(CXXFLAGS) -c Edge.cpp

# Rule to compile Demo.cpp into Demo.o
Demo.o: Demo.cpp Player.hpp Board.hpp Catan.hpp DevelopmentCard.hpp Hexigon.hpp Vertex.hpp Edge.hpp
	$(CXX) $(CXXFLAGS) -c Demo.cpp

# Clean up object files and executable
clean:
	rm -f $(OBJS) $(TARGET)
