CXX = g++
CXXFLAGS = -std=c++20 -Isrc
LIBS = -lraylib

# List of source files
SRCS = src/main.cpp src/GameLogic.cpp src/draw.cpp

# Generate object files from source files
OBJS = $(SRCS:.cpp=.o)


run:
	./main.out

game: $(OBJS)
	$(CXX) $(OBJS) -o main.out $(LIBS)

main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

GameLogic.o: src/GameLogic.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

draw.o: src/draw.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) main.out
