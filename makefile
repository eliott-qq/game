CXX = g++
CXXFLAGS = -std=c++11 -Wall

SOURCES = main.cpp game.cpp record.cpp utils.cpp fruitpool.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = memory_game

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean