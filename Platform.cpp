#include "Platform.h"

Platform::Platform(const char* filename, float posX, float posY, float scale, float width) {
    texture = LoadTexture(filename);
    this->posX = posX;
    this->posY = posY;
    this->scale = scale;
    this->width = width;
}

// Draw the platform
void Platform::draw() {

    Vector2 position = { posX, posY };

    DrawTextureEx(texture, position, 0.0f, scale, WHITE);
}

void Platform::unload() {
    UnloadTexture(texture);
}
