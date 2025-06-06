#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "raylib.h"

class Background {
public:

    // Constructor to initialize the background with textures
    Background(const char* texture_sky, const char* texture_sides, const char* texture_ground, const char* texture_decor, const char* texture_clouds, const char* texture_background, float bgY1);

    void draw(int windowHeight);

    void drawDecor(int windowHeight);

    void unload();

    Texture2D sky;
    Texture2D sides;
    Texture2D ground;
    Texture2D decor;
    Texture2D clouds;
    Texture2D backGround;

    float bgY1 = 0.0f;
protected:

private:
};

#endif