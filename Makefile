CC=g++
CPP_FLAGS=-g -Wall
LIBRARY_FLAGS=-lntl -lgmp

TEST_SRCS=$(wildcard tests/*.cpp)
TEST_EXES=$(TEST_SRCS:%.cpp=%.out)

CPP_SRCS=$(wildcard *.cpp)
CPP_OBJS=$(CPP_SRCS:%.cpp=%.o)

%.o: %.cpp
	$(CC) $(CPP_FLAGS) -c $< -o $@ $(LIBRARY_FLAGS)

%.out: %.cpp $(CPP_OBJS)
	$(CC) $(CPP_FLAGS) $< $(CPP_OBJS) -o $@ $(LIBRARY_FLAGS)

test: $(TEST_EXES)
	@echo "Running tests..."
	@for test_executable in $(TEST_EXES); do \
		echo "Running $$test_executable"; \
		$$test_executable; \
	done

clean:
	rm -rf $(TEST_EXES) $(CPP_OBJS)
