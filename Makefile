CC = g++
CFLAGS = -g -Wall
OBJ_DIR = obj
SRC_DIR = src

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

TARGET = raytracer
OUT_IMG = output.ppm

all: $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

clean:
	$(RM) $(OBJ) $(TARGET) $(OUT_IMG)
