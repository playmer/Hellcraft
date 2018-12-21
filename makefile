# Standard makefile I can drag and drop into projects to build them
# Declaration of variables
CC = g++
CC_FLAGS = -std=c++17 -Wall -g
 
# File names
EXEC = build # Called build because it is our current project build 
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
 
# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)
 
# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@
 
# To remove generated files
clean:
	del /F $(EXEC) $(OBJECTS)