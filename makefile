CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g

SRCS = main.cpp Asset.cpp Computer.cpp Desktop.cpp InventoryManager.cpp Mobile.cpp Server.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = program

$(TARGET): $(OBJS)
	$(CXX) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean
