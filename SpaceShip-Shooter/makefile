CXX = g++
CXXFLAGS = -std=c++20 -Isrc
LIBS = -lraylib

# List of source files
SRCS = src/game_logic/GameLogic.cpp src/rendering/draw.cpp
# Generate object files from source files
OBJS = $(SRCS:.cpp=.o)

TESTS = test/doctest.cpp test/GameLogicTest.cpp
TEST_OBJS = $(TESTS:.cpp=.o)

.PHONY: test

run:
	./main.out

game: $(OBJS) main.o
	$(CXX) $(OBJS) main.o -o main.out $(LIBS)

main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to compile source files
src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


test: CXXFLAGS += -Itest  # Add test directory to include path
test: $(OBJS) $(TEST_OBJS)
	$(CXX) $(OBJS) $(TEST_OBJS) -o test.out $(LIBS)

verify:
	./test.out

# Rule to compile test source files
test/%.o: test/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f src/**/*.o 
	rm -f test/*.o
	rm -f *.o
	rm -f *.out
