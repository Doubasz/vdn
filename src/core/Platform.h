#ifndef PLATFORM_H
#define PLATFORM_H

#include "Entity.h"

enum TypeTile{
    SAND,
    ROCK,
};


class Platform : public Entity{

private:
    int type;

public:
    Platform();
    Platform(int x, int y);

    void update() override;

};


#endif