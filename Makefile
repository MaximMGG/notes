MAIN = note.out
CC = gcc
LIB = -lncurses

SRC_DR = src/
SRCL_DR = lib/
OBJ_DR = obj/

SRC = $(wildcard $(SRC_DR)*.c $(SRCL_DR)*.c)
OBJ = $(patsubst $(SRC_DR)%.c, $(OBJ_DR)%.o, $(SRC))


$(MAIN): $(OBJ)
	$(CC) -o $(MAIN) $(OBJ) $(LIB)  

$(OBJ_DR)%.o:$(SRC_DR)%.c
	$(CC) -o $@ -c $^

clean:
	rm $(OBJ_DR)*.o $(MAIN)

debug:
	$(CC) $(SRC) $(LIB) -g
