CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -s -static -static-libgcc -static-libstdc++ -Iinclude
TARGET = dna_my_module

SRCS = main.cpp \
       src/common/SequenceRecord.cpp \
       src/common/DNAUtils.cpp \
       src/common/ISequenceIndex.cpp \
       src/linkedlist/UploadHistory.cpp \
       src/linkedlist/RecentSequenceList.cpp \
       src/tree/BinarySearchTree.cpp \
       src/tree/AVLTree.cpp \
       src/tree/MinHeap.cpp \
       src/tree/MaxHeap.cpp \
       src/tree/FenwickTree.cpp \
       src/tree/DNARangeIndex.cpp \
       src/map/SequenceMapIndex.cpp \
       src/map/KmerService.cpp \
       src/stl/STLUtilities.cpp \
       src/menu/MyModuleMenu.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe *.o

run: $(TARGET)
	./$(TARGET)

test: $(TARGET)
	./$(TARGET) --test
