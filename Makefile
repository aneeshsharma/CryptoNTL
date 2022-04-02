CC=g++
CPP_FLAGS=-g -Wall -lNTL

TEST_SRCS=$(wildcard tests/*.cpp)
TEST_EXES=$(TEST_SRCS:*.cpp=*.o)

CPP_SRCS=$(wildcard *.cpp)
CPP_OBJS=$(CPP_SRCS:*.cpp=*.o)

*.o: *.c
	$(CC) $(CPP_FLAGS) $< -o $@

test: $(TEST_EXES)
	echo "test"
