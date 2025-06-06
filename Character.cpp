#include "Character.h"

// Constructor implementation
Character::Character(const char *filename, int spriteWidth, int spriteHeight, int spriteRow, int spriteCount, int spritesPerSecond, float posX, float posY, float scale, bool isJumping)
{
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

    // Load jump sounds
    jumpSounds[0] = LoadSound("JumpSounds/sound1.wav");
    jumpSounds[1] = LoadSound("JumpSounds/sound2.wav");
    jumpSounds[2] = LoadSound("JumpSounds/sound3.wav");
    jumpSounds[3] = LoadSound("JumpSounds/sound4.wav");
    jumpSounds[4] = LoadSound("JumpSounds/sound5.wav");
    jumpSounds[5] = LoadSound("JumpSounds/sound6.wav");
    jumpSounds[6] = LoadSound("JumpSounds/sound7.wav");
}

void Character::move(float deltaTime, int windowWidth)
{
    float speed = 200.0f; // Movement speed in pixels per second

    if (IsKeyDown(KEY_D) && posX + spriteWidth * scale <= windowWidth + spriteWidth - border)
    {
        posX += speed * deltaTime;
    }
    if (IsKeyDown(KEY_A) && posX >= 0 - spriteWidth + border)
    {
        posX -= speed * deltaTime;
    }
}


void Character::jump(float deltaTime, int windowHeight)
{   
    int sprite_bottom = posY + sprite_size; // Bottom of the sprite

    if (sprite_bottom >= windowHeight)
    {
        isJumping = false; // Reset jumping state
        velocity = 0;
    }

    if (IsKeyPressed(KEY_SPACE) && !isJumping)
    {   
        // Play a random jump sound
        int randomIndex = GetRandomValue(0, 5);
        PlaySound(jumpSounds[randomIndex]); 

        velocity = -20;
        isJumping = true; // Set jumping state
    }

    posY += velocity; // Apply jump velocity
    velocity += 1;    // Gravity effect
}

// Draw the character with animation
void Character::draw() {
    int spriteIndex = (int)(GetTime() * spritesPerSecond) % spriteCount; // Select sprite frame

    Rectangle spriteRec = {
        (float)spriteIndex * spriteWidth, // X position in sprite sheet
        (float)spriteRow * spriteHeight,  // Y position in sprite sheet (row selection)
        facingLeft ? -(float)spriteWidth : (float)spriteWidth,
        (float)spriteHeight};

    Rectangle spriteDest = {
        posX, posY,
        (float)spriteWidth * scale, (float)spriteHeight * scale // Scale up the sprite
    };

    Vector2 origin = {0, 0}; // No rotation

    DrawTexturePro(texture, spriteRec, spriteDest, origin, 0.0f, WHITE);
}

void Character::update(float deltaTime)
{

    if (!isJumping && (IsKeyDown(KEY_D) || IsKeyDown(KEY_A)))
    {
        // walk
        spriteRow = 2;
        spriteCount = 4;
        spritesPerSecond = 3;
        facingLeft = IsKeyDown(KEY_A);
        idleTimer = 0.0;
    }
    else if (isJumping)
    {
        // jump
        spriteRow = 5;
        spriteCount = 1;
        facingLeft = IsKeyDown(KEY_A);
        idleTimer = 0.0;
    }
    else
    {
        // stand
        spriteRow = 0;
        spriteCount = 1;
        idleTimer += deltaTime;
        if (idleTimer >= 3.0f)
        {
            // idle
            spriteRow = 0;
            spriteCount = 26;
            spritesPerSecond = 5;
        }
    }
}

void Character::unload() {

    // Unload texture
    UnloadTexture(texture);

    // Unload sound
    UnloadSound(jumpSounds[0]);
    UnloadSound(jumpSounds[1]);
    UnloadSound(jumpSounds[2]);
    UnloadSound(jumpSounds[3]);
    UnloadSound(jumpSounds[4]);
    UnloadSound(jumpSounds[5]);
    UnloadSound(jumpSounds[6]);
}