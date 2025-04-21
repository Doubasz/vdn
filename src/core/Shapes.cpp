
#include "Shapes.h"
#include <cstdlib> // abs()




Point::Point(float x, float y): x(x), y(y) {}


Point::Point(): x(0), y(0) {}


Rectangle::Rectangle(float x, float y, int w, int h): x(x), y(y), w(w), h(h) {
	this->update();
}


Rectangle::Rectangle(): x(0), y(0), w(1), h(1){
	this->update();
}

Rectangle::Rectangle(Rectangle* other){
	this->copy(other);
}

void Rectangle::copy(Rectangle* other){
	this->x = other->x;
	this->y = other->y;
	this->w = other->w;
	this->h = other->h;

	this->update();
}

void Rectangle::addX(float x){
	this->x += x;

	this->update();
}


void Rectangle::addY(float y){
	this->y += y;

	this->update();
}

void Rectangle::setX(float x){
	this->x = x;

	this->update();
}

void Rectangle::setY(float y){
	this->y = y;

	this->update();
}





void Rectangle::update(){
	this->top    = y;
	this->bottom = y + h;

	this->leftMost  = x;
	this->rightMost = x + w;

	this->center = Point(x + (w/2),
	                     y + (h/2));

	this->topLeft     = Point(x,     y);
	this->topRight    = Point(x + w, y);
	this->bottomLeft  = Point(x,     y + h);
	this->bottomRight = Point(x + w, y + h);

	this->topCenter    = Point(center.x,  top);
	this->bottomCenter = Point(center.x,  bottom);
	this->leftCenter   = Point(leftMost,  center.y);
	this->rightCenter  = Point(rightMost, center.y);
}

bool Rectangle::overlaps(const Rectangle& other) const {
    return (
        x <= other.rightMost &&
        other.x <= rightMost &&
        y <= other.bottom &&
        other.y <= bottom
    );
}
bool Rectangle::overlaps(Rectangle* other)
{
    if (other == nullptr) return false;

    if ((x <= other->rightMost) &&
        (other->x <= rightMost) &&
        (y <= other->bottom) &&
        (other->y <= bottom))
        return true;

    return false;
}



void Rectangle::placeOnTop(Rectangle other){
	this->y = (other.y - this->h);

	this->update();
}
// Dans Shapes.cpp


bool Rectangle::overlaps(Rectangle other) {
    return this->overlaps(&other);
}



Circle::Circle(float x, float y, int r): x(x), y(y), r(r) {
	this->centerX = x + r;
	this->centerY = y + r;
}

void Circle::addX(float x){
	this->x       += x;
	this->centerX += x;
}

void Circle::addY(float y){
	this->y       += y;
	this->centerY += y;
}


std::string Rectangle::toString(){
    std::ostringstream oss;
    oss << "Rect : (x: " << x << ", y: " << y << "), (w: " << w << ", h: " << h << ")";
    return oss.str();
}