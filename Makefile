CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -O2

TARGET := dna_analyzer
TEST_TARGET := dna_tests

MODULE_SOURCES := searching.cpp \
                  graph.cpp \
                  dna_generator.cpp \
                  replication.cpp \
                  translation.cpp \
                  transformation.cpp \
                  comparison.cpp \
                  sorting.cpp    \
                  test_data.cpp

MAIN_SOURCES := main.cpp $(MODULE_SOURCES) tests.cpp
TEST_SOURCES := tests.cpp $(MODULE_SOURCES)

all: $(TARGET)

$(TARGET): $(MAIN_SOURCES)
	$(CXX) $(CXXFLAGS) -DDNA_TESTS_AS_LIBRARY $(MAIN_SOURCES) -o $(TARGET)

$(TEST_TARGET): $(TEST_SOURCES)
	$(CXX) $(CXXFLAGS) $(TEST_SOURCES) -o $(TEST_TARGET)

run: $(TARGET)
	./$(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET)

.PHONY: all run test clean
