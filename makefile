# Standard makefile I can drag and drop into projects to build them
# Declaration of variables
CC = g++
CC_FLAGS = -std=c++17 -Wall -g
LINKER_FLAGS =  -lsfml-graphics -lsfml-window -lsfml-system -mwindows
INCLUDE_FILES = C:\Users\Rietty\Documents\Libraries\SFML-Install\include
LIB_FILES = C:\Users\Rietty\Documents\Libraries\SFML-Install\lib
 
# File names
EXEC = Release/Hellcraft # Called build because it is our current project build 
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
 
all: $(EXEC)

# Main target
$(EXEC): $(OBJECTS)
	$(CC) -L $(LIB_FILES) $(OBJECTS) -o $(EXEC) $(LINKER_FLAGS)
 
# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@ -I $(INCLUDE_FILES)
 
# To remove generated files
clean:
	del /F $(OBJECTS)