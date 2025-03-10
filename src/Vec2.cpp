
#include "Vec2.h"


Vec2::Vec2(int a, int b) : x(a), y(b) {}
Vec2::Vec2() : x(0), y(0) {}

bool Vec2::operator== (const Vec2& other) const{
    return x == other.x && y == other.y;
}

std::ostream& operator<<(std::ostream& os, const Vec2& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os; // Return the stream to allow chaining
} 


void displayTab(std::vector<Vec2> tab){
    if(tab.empty()){
        std::cout << "empty" << std::endl;
        return;
    } 

    std::cout << "posi: ";
    for(size_t i = 0; i < tab.size(); i++){
        std::cout << tab[i];
        if(i != tab.size() - 1){
            std::cout << ", ";
        }
    }
    std::cout << "\n";
}


