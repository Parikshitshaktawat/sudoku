# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Iimgui
LDFLAGS = -lglfw -lGL -lGLU -lGLEW -ldl

# Executable name
TARGET = sudoku_app

# Source files
SRCS = main.cpp sudoku.cpp imgui/imgui.cpp imgui/imgui_draw.cpp imgui/imgui_widgets.cpp imgui/imgui_tables.cpp imgui/imgui_impl_glfw.cpp imgui/imgui_impl_opengl3.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Build target
all: $(TARGET)

# Link the object files into the executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile the source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)
