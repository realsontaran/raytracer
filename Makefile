CC = g++
CFLAGS = -g -Wall -lm
OBJ_DIR = obj
SRC_DIR = src

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

TARGET = raytracer

all: dir $(TARGET)

dir:
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

clean:
	$(RM) -r $(OBJ) $(TARGET)
