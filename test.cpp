
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

struct Point{
    int x, y;

    Point(int x, int y) : x(x), y(y) {}
};

std::vector<std::vector<int>> gameMap;
std::vector<Point> platforms;


bool isDigit(char c){
    return c >= '0' && c <= '9';
}

enum TypeCase{
    NONE = -1,
    PLAYER = -2,
    ENNEMY = -3,
};

// Check if a coordinate is inside the map bounds
bool inBounds(int i, int j, const std::vector<std::vector<int>>& map) {
    return i >= 0 && j >= 0 && i < map.size() && j < map[0].size();
}

// Check if any of the 4 neighbors of (i, j) are NONE
bool neighborIsNone(const std::vector<std::vector<int>>& map, int i, int j) {
    const std::vector<std::pair<int, int>> directions = {
        { -1,  0 }, // north
        {  1,  0 }, // south
        {  0, -1 }, // west
        {  0,  1 }  // east
    };

    for (const auto& [di, dj] : directions) {
        int ni = i + di;
        int nj = j + dj;
        if (inBounds(ni, nj, map) && map[ni][nj] == NONE)
            return true;
    }

    return false;
}

void loadTileMap(){

    string path = "scripts/mapGeneration/level1.txt";

    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << path << std::endl;
        exit(-1);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<int> row;
        std::stringstream ss(line);
        int value;

        while (ss >> value) {
            row.push_back(value);
        }

        gameMap.push_back(row);

    }

    file.close();

    for(int i = 0; i < gameMap[0].size(); i++){
        for(int j = 0; j < gameMap.size(); j++){
            //std:: cout << "x : " << gameMap.size() << " y : " << gameMap[0].size() << std::endl;
            //std::cout<< "i : " << i << " j : " << j << std::endl;

            if(gameMap[j][i] != NONE && gameMap[j][i] != PLAYER && gameMap[j][i] != ENNEMY){
                if(neighborIsNone(gameMap, j, i)){
                    platforms.push_back({i, j});
                }
            }

        }
    }
}

/*int value;
        string temp;
        
        for(int i = 0; i < line.length(); i++){
            if(isDigit(line[i])){
                temp += line[i];
            }
            else{
                if(temp != ""){
                    value = std::stoi(temp);
                    row.push_back(value);
                }
                
                temp = "";
            }
        }

        tilemap.push_back(row);*/


void displayMap(const std::vector<std::vector<int>>& vec){
    /*for (const auto& row : vec) {
        for (int tile : row) {
            std::cout << tile << " ";
        }
        std::cout << std::endl;
    }*/

    for(int i = 0; i < gameMap[0].size(); i++){
        for(int j = 0; j < gameMap.size(); j++){

            if(gameMap[j][i] != NONE && gameMap[j][i] != PLAYER && gameMap[j][i] != ENNEMY){
                if(neighborIsNone(gameMap, j, i)){
                    std::cout << "#";
                }
                else{
                    std::cout << "+";
                }
            }
            else{
                std::cout << ".";
            }
            std::cout << " ";

        }
        std::cout << endl;
    }
}

int main(void){

    std::vector<std::vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    loadTileMap();
    displayMap(gameMap);

    return 0;
}