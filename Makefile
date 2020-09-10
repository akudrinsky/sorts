SRC_DIR := src
OBJ_DIR := bin
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
LDFLAGS := -Wall
CPPFLAGS := -std=c++17

executable: $(OBJ_FILES)
	g++ $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CPPFLAGS) -c -o $@ $<

experiment: experiments/experiments.cpp
	g++ -arch x86_64 -framework OpenGL -I/usr/local/include -L/usr/local/lib  -o experiments/experiment experiments/experiments.cpp -lglfw.3 -lGLEW.2.1.0

genArrays: data/gen-sort-tests.py
	./data/gen-sort-tests.py