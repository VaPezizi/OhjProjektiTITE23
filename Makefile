CXX = g++
CXXFLAGS = -Wall -Iinclude -lraylib 
SRCDIR = src
OBJDIR = build
TARGET = main

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(CXXFLAGS) -g -o $@ 

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) -c $< $(CXXFLAGS) -g -o $@ 


$(OBJDIR):
	mkdir -p $(OBJDIR)
clean:
	rm -rf $(OBJDIR) $(TARGET)

#pixelDraw: main.cpp
#	g++ main.cpp -o main.o -Wall -Wextra -lraylib
