CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -I include
TARGET = CarRent
BUILD_DIR = build

SOURCES = src/main.cpp \
          src/vehicle.cpp \
          src/renter.cpp \
          src/rent_record.cpp \
          src/utils.cpp \
          src/auth.cpp \
          src/logger.cpp \
          src/vehicle_manager.cpp \
          src/renter_manager.cpp \
          src/rent_manager.cpp \
          src/receipt.cpp \
          src/statistics.cpp \
          src/ui.cpp

OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean run distclean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)

distclean: clean
	rm -f *.dat *.txt log.txt
