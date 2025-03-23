
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

std::vector<std::vector<int>> tilemap;


bool isDigit(char c){
    return c >= '0' && c <= '9';
}



void loadTileMap(){

    string path = "../mapGeneration/gameMap1.txt";

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

        tilemap.push_back(row);

    }

    file.close();
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
    for (const auto& row : vec) {
        for (int tile : row) {
            std::cout << tile << " ";
        }
        std::cout << std::endl;
    }
}

int main(void){

    std::vector<std::vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    loadTileMap();
    displayMap(tilemap);

    return 0;
}