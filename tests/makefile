# Compilateur et flags
CXX        := g++
CXXFLAGS   := -std=c++17 -Wall -Wextra -g \
               -I../src/core -I../src/sdl2 -I../src/txt -I/usr/include/SDL2
TEST_FLAGS := -I/usr/local/include   # chemin vers googletest/include

# Bibliothèques de test
LIBS_TEST  := -L/usr/local/lib -lgtest -lgtest_main -lpthread -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_image

# Répertoires
SRX_TEST   := src
SRX_CORE   := ../src/core
SRX_SDL2   := ../src/sdl2
OBJ_DIR    := obj
BIN_DIR    := bin

# Sources
TEST_SRC   := $(wildcard $(SRX_TEST)/*.cpp) $(SRX_TEST)/MenuStateTest.cpp
CORE_SRC   := $(wildcard $(SRX_CORE)/*.cpp)
# Exclusion de main.cpp
SDL2_SRC   := $(filter-out $(SRX_SDL2)/main.cpp,$(wildcard $(SRX_SDL2)/*.cpp))

# Objets générés
TEST_OBJS  := $(patsubst $(SRX_TEST)/%.cpp,$(OBJ_DIR)/%.o,$(TEST_SRC))
CORE_OBJS  := $(patsubst $(SRX_CORE)/%.cpp,$(OBJ_DIR)/%.o,$(CORE_SRC))
SDL2_OBJS  := $(patsubst $(SRX_SDL2)/%.cpp,$(OBJ_DIR)/%.o,$(SDL2_SRC))

# Exécutables
EXEC_CAMERA := $(BIN_DIR)/camera
EXEC_ENNEMY := $(BIN_DIR)/ennemy
EXEC_LEVEL  := $(BIN_DIR)/level
EXEC_PLAYER := $(BIN_DIR)/player
EXEC_BUTTON := $(BIN_DIR)/button_test # Binaire pour les tests de Button


.PHONY: all camera ennemy level player button_test  run_camera run_ennemy run_level run_button_test  clean

# Cible par défaut
all: camera ennemy level player button_test menu_test

# --- Tests Camera ---
camera: $(TEST_OBJS) $(CORE_OBJS) $(SDL2_OBJS)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_FLAGS) $(OBJ_DIR)/CameraTest.o $(CORE_OBJS) $(SDL2_OBJS) -o $(EXEC_CAMERA) $(LIBS_TEST)

run_camera: camera
	./$(EXEC_CAMERA)

# --- Tests Ennemy ---
ennemy: $(TEST_OBJS) $(CORE_OBJS) $(SDL2_OBJS)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_FLAGS) $(OBJ_DIR)/EnnemyTest.o $(CORE_OBJS) $(SDL2_OBJS) -o $(EXEC_ENNEMY) $(LIBS_TEST)

run_ennemy: ennemy
	./$(EXEC_ENNEMY)

# --- Tests Level ---
level: $(TEST_OBJS) $(CORE_OBJS) $(SDL2_OBJS)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_FLAGS) $(OBJ_DIR)/LevelTest.o $(CORE_OBJS) $(SDL2_OBJS) -o $(EXEC_LEVEL) $(LIBS_TEST)

run_level: level
	./$(EXEC_LEVEL)

# --- Tests Player ---
player: $(TEST_OBJS) $(CORE_OBJS) $(SDL2_OBJS)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_FLAGS) $(OBJ_DIR)/PlayerTest.o $(CORE_OBJS) $(SDL2_OBJS) -o $(EXEC_PLAYER) $(LIBS_TEST)

run_player: player
	./$(EXEC_PLAYER)

# --- Tests Button ---
button_test: $(TEST_OBJS) $(CORE_OBJS) $(SDL2_OBJS)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_FLAGS) $(OBJ_DIR)/ButtonTest.o $(CORE_OBJS) $(SDL2_OBJS) -o $(EXEC_BUTTON) $(LIBS_TEST)

run_button_test: button_test
	./$(EXEC_BUTTON)

# --- Tests MenuState ---


# Règle pour compiler les tests dans obj/
$(OBJ_DIR)/%.o: $(SRX_TEST)/%.cpp
	@echo "Compiling test file: $<"
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_FLAGS) -c $< -o $@

# Règle pour compiler les sources core dans obj/
$(OBJ_DIR)/%.o: $(SRX_CORE)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Règle pour compiler les sources SDL2 dans obj/
$(OBJ_DIR)/%.o: $(SRX_SDL2)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
