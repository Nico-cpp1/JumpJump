#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"

class Character {
public:
    // Constructor to initialize the character with a texture and sprite details
    Character(const char* filename, int spriteWidth, int spriteHeight, int spriteRow, int spriteCount, int spritesPerSecond, float posX, float posY, float scale, bool isJumping);

    // Function to update the character's movement
    void move(float deltaTime, int windowWidth);

    // Function to draw the character on the screen
    void draw();

    void jump(float deltaTime, int windowHeight);

    int spriteRow; // The row in the sprite sheet
    int spriteCount; // Number of sprites in the row
    int spritesPerSecond; // How fast the sprite animation runs
    int spriteHeight = 16;
    int spriteWidth = 16;
    bool facingLeft = false;
    float idleTimer = 0.0f;
    float scale = 6.0f;
    bool isJumping  = false;
    float currentFrame = spriteCount; // Current frame of the animation
    float posX; // Character's X position
    float posY; // Character's Y position
    int velocity = 4;
    int sprite_size = spriteHeight * scale; // Size of the sprite

protected:

private:
    Texture2D texture; // The character's texture
};

#endif
