CXX := clang
CXX_FLAGS := -pedantic-errors -Wall -Wextra -Wconversion -Werror -std=c89

EXECUTABLE := 1

run: $(EXECUTABLE)
	@echo "Executing..."
	ls
	./$(EXECUTABLE).exe

$(EXECUTABLE): start
	@echo "Building $(EXECUTABLE)..."
	$(CXX) $(CXX_FLAGS) --output=./$(EXECUTABLE).exe main.c

start:
	@echo "Starting..."
