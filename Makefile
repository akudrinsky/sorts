SRC_DIR := src
OBJ_DIR := bin
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
LDFLAGS := -Wall -lsfml-graphics -lsfml-window -lsfml-system
CPPFLAGS := -std=c++17 # -g3

executable: $(OBJ_FILES)
	g++ $(LDFLAGS) -o $@ $^ 

clean:
	rm bin/*.o

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CPPFLAGS) -c -o $@ $<

experiment: experiments/experiments.cpp
	g++ experiments/experiments.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system && ./sfml-app
#g++ -arch x86_64 -framework OpenGL -I/usr/local/include -L/usr/local/lib  -o experiments/experiment experiments/experiments.cpp -lglfw.3 -lGLEW.2.1.0

genArrays: data/gen-sort-tests.py
	./data/gen-sort-tests.py

show: executable
	./executable show >./data/logs.txt