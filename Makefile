# Compiler
CXX = g++

# Linker flags
LDFLAGS = -lGL -lglfw -lGLEW

# Directories
SRCDIR = src
BUILDDIR = build

# Source files and object files
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SRCS))

# Output executable
TARGET = exec

# Build target executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)


# Compile source files into object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(BUILDDIR)
	$(CXX) -c $< -o $@

# Clean
clean:
	rm -rf $(BUILDDIR) $(TARGET)
