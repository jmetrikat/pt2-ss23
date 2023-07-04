COMPILER = clang++
OPTIONS = -std=c++17 -g
TEST_OPTIONS = -std=c++17 -Idoctest/doctest -Wall -pedantic -g
BUILD=../out
TESTS=../tests

COMPILE= $(COMPILER) $(OPTIONS)
TEST_COMPILE= $(COMPILER) $(TEST_OPTIONS)

all: tests bloom_cli trie_cli

main: prep
	$(COMPILE) -o ../out/main ../src/main.cpp

bloom_cli: prep
	$(COMPILE) -o ../out/bloom_cli ../src/bloom_cli.cpp

trie_cli: prep
	$(COMPILE) -o ../out/trie_cli ../src/trie_cli.cpp

tests: prep
	$(TEST_COMPILE) $(TESTS)/tests.cpp -o $(BUILD)/tests
	chmod +x $(BUILD)/tests

.PHONY: clean prep
clean: 
	rm -rf $(BUILD)
prep: 
	mkdir -p $(BUILD)