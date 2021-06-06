CXX := clang
CXX_FLAGS := -pedantic-errors -v -Wall -Weffc++ -Wextra -Wsign-conversion -Werror -std=c++17

LIBRARIES := glfw3dll.lib glad.c
EXECUTABLE := main

run: $(EXECUTABLE)
	clear
	@echo "🚀  Executing..."
	./$(EXECUTABLE).exe

$(EXECUTABLE): start
	@echo "🏗️  Building $(EXECUTABLE)..."
	$(CXX) -l$(LIBRARIES) --output=$(EXECUTABLE).exe $(EXECUTABLE).cpp

start:
	@echo "🚧  Starting..."