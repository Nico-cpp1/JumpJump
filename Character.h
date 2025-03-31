#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"

class Character {
public:
    // Constructor to initialize the character with a texture and sprite details
    Character(const char* filename, int spriteWidth, int spriteHeight, int spriteRow, int spriteCount, int spritesPerSecond, float posX, float posY);

    // Function to update the character's movement
    void move(float deltaTime);

    // Function to draw the character on the screen
    void draw();

    int spriteRow; // The row in the sprite sheet
    int spriteCount; // Number of sprites in the row
    int spritesPerSecond; // How fast the sprite animation runs
    int spriteWidth;
    bool facingLeft = false;
    float idleTimer;

protected:

private:
    Texture2D texture; // The character's texture
    int spriteHeight;
    float posX; // Character's X position
    float posY; // Character's Y position
};

#endif
