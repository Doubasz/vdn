
#include "Vec2f.h"


Vec2f::Vec2f(float a, float b) : x(a), y(b) {}
Vec2f::Vec2f() : x(0), y(0) {}

bool Vec2f::operator== (const Vec2f& other) const{
    return x == other.x && y == other.y;
}

std::ostream& operator<<(std::ostream& os, const Vec2f& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os; // Return the stream to allow chaining
} 


void displayTab(std::vector<Vec2f> tab){
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


