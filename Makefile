CC=g++
CFLAGS= -Wall -std=c++0x -c -g 
INC= -I/usr/include/espeak -Iinc
TARGET = robot
BUILD_PATH = ./build
BIN_PATH = ./bin
OBJ = main.o robot.o speak.o envcanada.o rpi_io.o face.o color.o pca9685.o pwmrgbled.o
OBJS = $(OBJ:%.o=$(BUILD_PATH)/%.o)

.PHONY: clean 

all: $(TARGET) 

$(TARGET): $(OBJS) 
	$(CC) -o $(BIN_PATH)/$@ $(OBJS) -lespeak -lcurl -lwiringPi

$(BUILD_PATH)/%.o: %.cpp 
	$(CC) $(CFLAGS) $(INC) $< -o $@

clean:
	rm -rf $(BUILD_PATH)/*o $(BIN_PATH)/$(TARGET) 

install: all
	cp $(BIN_PATH)/$(TARGET) /bin/$(TARGET)	

