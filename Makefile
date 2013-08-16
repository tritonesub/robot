CC=g++
CFLAGS= -Wall -std=c++0x -c
INC= -I/usr/include/espeak -Iinc
TARGET = robot
BUILD_PATH = ./build
BIN_PATH = ./bin
OBJ = main.o robot.o speak.o envcanada.o
OBJS = $(OBJ:%.o=$(BUILD_PATH)/%.o)

.PHONY: clean

all: $(TARGET) 

$(TARGET): $(OBJ) 
	$(CC) -lespeak -lcurl -l bcm2835 -o $(BIN_PATH)/$@ $(OBJS) 

%.o: %.cpp 
	$(CC) $(CFLAGS) $(INC) $< -o $(BUILD_PATH)/$@

clean:
	rm -rf $(BUILD_PATH)/*o $(BIN_PATH)/$(TARGET) 

install: all
	cp $(BIN_PATH)/$(TARGET) /bin/$(TARGET)	
