# Compilateur
CC = gcc

# Nom de l'exécutable
EXEC = pacman

# Dossiers
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include

# Sources et objets
SRC = $(wildcard $(SRC_DIR)/*.c) main.c
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))  # <- supprime 'src/' dans obj

# Flags compilation et linker SDL2
CFLAGS = -Wall -Wextra -g -I$(INCLUDE_DIR) `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_ttf

# Règle par défaut
all: $(BIN_DIR)/$(EXEC)

# Compilation .c -> .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compilation main.c séparément
$(OBJ_DIR)/main.o: main.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Création de l'exécutable
$(BIN_DIR)/$(EXEC): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# Nettoyage
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)/$(EXEC)
