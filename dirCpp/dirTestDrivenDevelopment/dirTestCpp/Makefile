# Condition Variable Demo Makefile
GOOGLE_TEST_LIB = gtest
GOOGLE_TEST_INCLUDE = /home/tub/Documents/dirGitResources/dirTestDrivenDevelopment/googletest/googletest/include
GOOGLE_TEST_LD_FLAGS = -L /home/tub/Documents/dirGitResources/dirTestDrivenDevelopment/googletest/dirBuild/lib

CXX	 = g++
CXXFLAGS = -Wall -std=c++17 -g -I $(GOOGLE_TEST_INCLUDE) $(GOOGLE_TEST_LD_FLAGS)
TARGET = main
SRC = main.cpp
LDLIBS = -lboost_thread -lboost_system -l $(GOOGLE_TEST_LIB) -l pthread


$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(LDLIBS) -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)

