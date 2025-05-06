#include "Character.h"
#include "raylib.h"

// Constructor implementation
    Character::Character(const char* filename, int spriteWidth, int spriteHeight, int spriteRow, int spriteCount, int spritesPerSecond, float posX, float posY, float scale, bool isJumping) {
    texture = LoadTexture(filename);
    this->spriteWidth = spriteWidth;
    this->spriteHeight = spriteHeight;
    this->spriteRow = spriteRow;
    this->spriteCount = spriteCount;
    this->spritesPerSecond = spritesPerSecond;
    this->posX = posX;
    this->posY = posY;
    this->scale = scale;
    this->isJumping = isJumping;
}

void Character::move(float deltaTime, int windowWidth) {
    float speed = 200.0f; // Movement speed in pixels per second

    if (IsKeyDown(KEY_D) && posX + spriteWidth * scale <= windowWidth + spriteWidth) {
        posX += speed * deltaTime;
    }
    if (IsKeyDown(KEY_A) && posX >= 0 - spriteWidth) {
        posX -= speed * deltaTime;
    }
}

void Character::jump(float deltaTime, int windowHeight) {
    int sprite_bottom = posY + sprite_size; // Bottom of the sprite

    DrawText(TextFormat("Test1: %08i", (int)posY), 20, 20, 20, BLACK);
    if (sprite_bottom >= windowHeight) {
        isJumping = false; // Reset jumping state
        velocity = 0;
        posY = windowHeight - sprite_size; // Reset position to the bottom
    }

    if (IsKeyPressed(KEY_SPACE) && !isJumping) {
        velocity = -20;
        isJumping = true; // Set jumping state
    }

    posY += velocity; // Apply jump velocity
    velocity += 1; // Gravity effect
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
