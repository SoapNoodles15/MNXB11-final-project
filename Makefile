CXX := g++
CXXWARNINGS := -Wall -Wextra -Werror
CXXOPT := -O3
CXXSTD := -std=c++17
INCLUDES := -I include -I external/include  # Ensure these paths are correct

# ROOT
ROOTCFLAGS := $(shell root-config --cflags)
ROOTLIBS := $(shell root-config --glibs)

CXXFLAGS := $(CXXWARNINGS) $(CXXSTD) $(CXXOPT) $(INCLUDES) $(ROOTCFLAGS)

# Source files
SRCS := src/coldwarm.cxx main.cxx  # main.cxx is in the root directory
OBJS := src/coldwarm.o src/main.o    # Define object files explicitly

# Target executable
TARGET := main

# Default rule to build the target
all: $(TARGET)

# Rule to link the object files into the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(ROOTLIBS)

# Rule to compile .cxx files into .o files
src/%.o: src/%.cxx
	$(CXX) $(CXXFLAGS) -c $< -o $@  # Compiles object files into src/

# Rule for main.cxx since it is in the root directory
src/main.o: main.cxx
	$(CXX) $(CXXFLAGS) -c $< -o $@  # Compile main.cxx into src/main.o

# Clean rule to remove object files and the executable
clean:
	rm -f src/*.o $(TARGET)