# Define the compiler
CXX = g++

# Define the compiler flags
CXXFLAGS = -Wall -g

# Define the libraries to link
LIBS = -lX11 -lXpm

# Define the source files
SRCS = $(wildcard *.cc)

# Define the object files
OBJS = $(SRCS:.cc=.o)

# Define the executable
EXEC = chess

# Default target
all: $(EXEC)

# Link the object files to create the executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS) $(LIBS)

# Compile the source files into object files
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean the build directory
clean:
	rm -f $(OBJS) $(EXEC)

# Phony targets
.PHONY: all clean
