CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = CarRent
BUILD_DIR = build

SOURCES = src/main.cpp

OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean run distclean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/main.o: src/simple_app.cpp src/menu1_vehicle.cpp src/menu2_renter.cpp src/menu3_rent.cpp src/menu4_return.cpp src/menu5_query.cpp src/menu6_statistics.cpp src/menu7_output.cpp src/menu8_system.cpp src/menu9_extended.cpp

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)

distclean: clean
	rm -f *.dat *.txt log.txt
