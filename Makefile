CXX := g++
CXXWARNINGS := -Wall -Wextra -Werror
CXXOPT := -O3
CXXSTD := -std=c++17
INCLUDES := 
LIBDIRS := 


CXXFLAGS := $(CXXWARNINGS) $(CXXSTD) $(CXXOPT) $(INCLUDES)
#LDFLAGS :=$(LIBDIRS)

# Source files and object files
SRCS := main.cxx  # Updated to use .cxx extension
OBJS := src/main.o

# Target executable
TARGET := main

# Default rule to build the target
all: $(TARGET)

# Rule to link the object files into the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBDIRS)

# Rule to compile .cxx files into .o files
src/%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove object files and the executable
clean:
	rm -f $(OBJS) $(TARGET)
