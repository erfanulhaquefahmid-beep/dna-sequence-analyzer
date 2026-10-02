CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -O2
CPPFLAGS := -Iinclude -Itests

TARGET := dna_analyzer
TEST_TARGET := dna_tests

rwildcard = $(foreach entry,$(wildcard $1*),$(call rwildcard,$(entry)/,$2)) $(wildcard $1$2)

SOURCE_PATTERNS := *.[cC][pP][pP] *.[cC][cC] *.[cC][xX][xX]
APP_SOURCES := $(sort $(foreach pattern,$(SOURCE_PATTERNS),$(call rwildcard,src/,$(pattern))))
MAIN_SOURCES := $(sort $(wildcard src/*[Mm]ain*.[cC][pP][pP] src/*[Mm]ain*.[cC][cC] src/*[Mm]ain*.[cC][xX][xX]))
CORE_SOURCES := $(filter-out $(MAIN_SOURCES),$(APP_SOURCES))
TEST_SOURCES := $(sort $(foreach pattern,$(SOURCE_PATTERNS),$(call rwildcard,tests/,$(pattern))))
HEADERS := $(sort $(foreach pattern,*.[hH] *.[hH][pP][pP],$(call rwildcard,include/,$(pattern)) $(call rwildcard,tests/,$(pattern))))

all: $(TARGET)

$(TARGET): $(MAIN_SOURCES) $(CORE_SOURCES) $(TEST_SOURCES) $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -DDNA_TESTS_AS_LIBRARY $(MAIN_SOURCES) $(CORE_SOURCES) $(TEST_SOURCES) -o $(TARGET)

$(TEST_TARGET): $(CORE_SOURCES) $(TEST_SOURCES) $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(CORE_SOURCES) $(TEST_SOURCES) -o $(TEST_TARGET)

run: $(TARGET)
	./$(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET)

.PHONY: all run test clean
