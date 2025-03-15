#ifndef VEC2F_H
#define VEC2F_H

#include <iostream>
#include <vector>


struct Vec2f{
    float x, y;

    Vec2f(float a, float b);
    Vec2f();

    bool operator== (const Vec2f& other) const;

    
};

// Overload the << operator
std::ostream& operator<<(std::ostream& os, const Vec2f& p);
void displayTab(std::vector<Vec2f> tab);


#endif