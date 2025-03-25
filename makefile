# Variables
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -I./src/core -I./src/sdl2 -I/usr/include/SDL2
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf
SRX_CORE = src/core
SRX_TXT = src/txt
SRX_SDL2 = src/sdl2
BIN_DIR = bin

# Liste des fichiers sources et objets
CORE_SRC = $(wildcard $(SRX_CORE)/*.cpp)
TXT_SRC = $(wildcard $(SRX_TXT)/*.cpp)
SDL2_SRC = $(wildcard $(SRX_SDL2)/*.cpp)
CORE_OBJS = $(CORE_SRC:.cpp=.o)
SDL2_OBJS = $(SDL2_SRC:.cpp=.o)

# Nom des exécutables
EXEC = $(BIN_DIR)/jeu
EXEC_SDL = $(BIN_DIR)/jeu_sdl

# Règle principale
all: $(EXEC)

# Génération de l'exécutable
$(EXEC): $(CORE_OBJS) $(TXT_SRC:.cpp=.o)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Génération de l'exécutable SDL sans src/txt
sdl: $(CORE_OBJS) $(SDL2_OBJS)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(EXEC_SDL) $(LIBS)

# Compilation des fichiers objets
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(SRX_CORE)/*.o $(SRX_TXT)/*.o $(SRX_SDL2)/*.o
	rm -f $(EXEC) $(EXEC_SDL)

# Nettoyage complet (avec le dossier bin)
distclean: clean
	rm -rf $(BIN_DIR)

# Phony targets
.PHONY: all clean distclean sdl
