TARGET_MAIN = ref

OBJECTS_MAIN = main.o func.o coef.cpp

CC = g++

CFLAGS = -c

# красный шрифт
RED_FONT = \033[31m
STANDART_FORMAT = \033[0m


all: $(OBJECTS_MAIN)
	$(CC) $(OBJECTS_MAIN) -o $(TARGET_MAIN)
	@echo "$(STANDART_FORMAT)run with formula: $(RED_FONT)./ref"
	
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

func.o: func.cpp
	$(CC) $(CFLAGS) func.cpp
	
coef.o: coef.cpp
	$(CC) $(CFLAGS) coef.cpp

	
.PHONY: clean
clean:
	-rm -f $(OBJECTS_MAIN) $(TARGET_MAIN)
