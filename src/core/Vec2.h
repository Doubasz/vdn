#ifndef VEC2_H
#define VEC2_H

#include <iostream>
#include <vector>


struct Vec2{
    int x, y;

    Vec2(int a, int b);
    Vec2();

    bool operator== (const Vec2& other) const;

    
};

// Overload the << operator
std::ostream& operator<<(std::ostream& os, const Vec2& p);
void displayTab(std::vector<Vec2> tab);


#endif