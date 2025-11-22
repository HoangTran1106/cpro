# Makefile cho SPWS

CC = gcc
CFLAGS = -Wall -std=c99
TARGET = spws

# cac file nguon
SRCS = main.c spws_controller.c hal_sensors.c hal_actuators.c hal_buttons.c

# cac file object
OBJS = main.o spws_controller.o hal_sensors.o hal_actuators.o hal_buttons.o

# build chuong trinh
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@echo "Build thanh cong!"

# bien dich cac file .c
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# don dep
clean:
	rm -f $(OBJS) $(TARGET)
	@echo "Da don dep"

# chay chuong trinh
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
