#ifndef CAMERA_H
#define CAMERA_H


#include <algorithm>

class Camera{

public:
    float x, y;
    int w, h;

    float targetX, targetY;

    bool smoothFollow;
    float followSpeed;

    int levelWidth, levelHeight;


    Camera() : x(0), y(0), w(0), h(0) {}

    Camera(int w, int h, int mapWidth, int mapHeight)
            : x(0), y(0), targetX(0), targetY(0),
            w(w), h(h),
            smoothFollow(false), followSpeed(5.0f),
            levelWidth(mapWidth), levelHeight(mapHeight) {
        }
    
    void update(float targetX, float targetY);

    float getX() const {return x;}
    float getY() const {return y;}

    void setSmoothFollow(bool smooth) {smoothFollow = smooth;}
    void setFollowSpeed(float s) {followSpeed = s;}
    void setLevelBoundaries(int w, int h) {levelWidth = w; levelHeight = h;}
};



#endif //CAMERA_H