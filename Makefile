CXX = g++
CXXFLAGS = -std=c++20 -Wall -O3 #-g -Iinclude

TARGET = test

all:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)


# Directories
SRC_DIR = .
# OBJ_DIR = obj

# Source files
SRCS = main.cpp

# Object files (put them in the obj directory)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Default rule to build the target
$(TARGET): 
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
# 	mkdir -p $(OBJ_DIR)
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(TARGET)

# Phony targets
.PHONY: clean
