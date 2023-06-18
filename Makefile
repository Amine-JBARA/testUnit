CXX = g++
CXXFLAGS = -pthread -lgtest -lgtest_main -lsqlite3

SRC_DIR = ./files
TEST_DIR = ./gtest-sqlite_interface

SRC_FILES = $(wildcard $(SRC_DIR)/sqlite_interface.cpp)
TEST_FILES = $(wildcard $(TEST_DIR)/*.cpp)

TARGET = main.exe

all: $(TARGET)

$(TARGET): $(SRC_FILES) $(TEST_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f $(TARGET)
