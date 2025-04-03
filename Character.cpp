#include "Character.h"
#include "raylib.h"

// Constructor implementation
    Character::Character(const char* filename, int spriteWidth, int spriteHeight, int spriteRow, int spriteCount, int spritesPerSecond, float posX, float posY) {
    texture = LoadTexture(filename);
    this->spriteWidth = spriteWidth;
    this->spriteHeight = spriteHeight;
    this->spriteRow = spriteRow;
    this->spriteCount = spriteCount;
    this->spritesPerSecond = spritesPerSecond;
    this->posX = posX;
    this->posY = posY;
}

// Move the character based on keyboard input
void Character::move(float deltaTime, int windowWidth) {
    float speed = 200.0f; // Movement speed in pixels per second

    if (IsKeyDown(KEY_D)&& posX <= windowWidth + spriteWidth * scale) {
        posX += speed * deltaTime;
    }
    if (IsKeyDown(KEY_A) && posX>= 0 -spriteWidth * scale) {
        posX -= speed * deltaTime;
    }
}

// Draw the character with animation
void Character::draw() {
    int spriteIndex = (int)(GetTime() * spritesPerSecond) % spriteCount; // Select sprite frame

    Rectangle spriteRec = {
        (float)spriteIndex * spriteWidth, // X position in sprite sheet
        (float)spriteRow * spriteHeight,  // Y position in sprite sheet (row selection)
        facingLeft ? -(float)spriteWidth : (float)spriteWidth,
        (float)spriteHeight
    };

    Rectangle spriteDest = {
        posX, posY, 
        (float) spriteWidth * scale, (float)spriteHeight * scale // Scale up the sprite
    };

    Vector2 origin = {0, 0}; // No rotation

    DrawTexturePro(texture, spriteRec, spriteDest, origin, 0.0f, WHITE);
}
