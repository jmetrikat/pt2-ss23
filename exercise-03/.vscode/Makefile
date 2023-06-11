COMPILER = clang++
OPTIONS = -std=c++17
TEST_OPTIONS = -std=c++17 -Idoctest/doctest -Wall -pedantic -g
BUILD=../out
TESTS=../tests

COMPILE= $(COMPILER) $(OPTIONS)
TEST_COMPILE= $(COMPILER) $(TEST_OPTIONS)

all: main tests

main: prep
	$(COMPILE) -o ../out/main ../src/main.cpp

tests: prep
	$(TEST_COMPILE) $(TESTS)/tests.cpp -o $(BUILD)/tests
	chmod +x $(BUILD)/tests

.PHONY: clean prep
clean: 
	rm -rf $(BUILD)
prep: 
	mkdir -p $(BUILD)