COMPILER = clang++
OPTIONS = -std=c++17
TEST_OPTIONS = -std=c++17 -Idoctest/doctest -Wall -pedantic -g
BUILD=../out
TESTS=../tests

COMPILE= $(COMPILER) $(OPTIONS)
TEST_COMPILE= $(COMPILER) $(TEST_OPTIONS)
VLIB=$(wildcard ../src/vlib/*.cpp)

all: tests routing

tests: prep
	$(TEST_COMPILE) $(TESTS)/tests.cpp $(VLIB) -o $(BUILD)/tests
	chmod +x $(BUILD)/tests

routing: prep
	$(COMPILE) $(VLIB) ../src/routing_cli.cpp -o $(BUILD)/routing
	chmod +x $(BUILD)/routing

.PHONY: clean prep
clean:
	rm -rf $(BUILD)
prep:
	mkdir -p $(BUILD)