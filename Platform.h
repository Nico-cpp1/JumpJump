#ifndef PLATFORM_H
#define PLATFORM_H

#include "raylib.h"

class Platform {
public:
    //Constructor to initialize the platforms position and texture
    Platform(const char* filename, float posX, float posY, float scale, float width);

    void draw();

    void unload();

    Texture2D texture;
    float posX;
    float posY;
    float scale;

    float width;

protected:

private:
};

#endif