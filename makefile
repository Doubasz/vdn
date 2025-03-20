# Variables
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./src/core -I./src/txt
SRX_CORE = src/core
SRX_TXT = src/txt
BIN_DIR = bin

# Liste des fichiers sources et objets
CORE_SRC = $(wildcard $(SRX_CORE)/*.cpp)
TXT_SRC = $(wildcard $(SRX_TXT)/*.cpp)
OBJS = $(CORE_SRC:.cpp=.o) $(TXT_SRC:.cpp=.o)

# Nom de l'exécutable
EXEC = $(BIN_DIR)/jeu

# Règle principale
all: $(EXEC)

# Génération de l'exécutable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compilation des fichiers objets
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(SRX_CORE)/*.o $(SRX_TXT)/*.o
	rm -f $(EXEC)

# Nettoyage complet (avec le dossier bin)
distclean: clean
	rm -rf $(BIN_DIR)

# Phony targets
.PHONY: all clean distclean
