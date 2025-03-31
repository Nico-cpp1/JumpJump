#include "raylib.h"
#include "Character.h"

int main() {
    // Window dimensions
    const int windowWidth = 600; //on laptop 600 // on Pc 720
    const int windowHeight = 900; // on laptop 900 // on PC 1280
    InitWindow(windowWidth, windowHeight, "JumpJump");

    // Load background
    Texture2D background = LoadTexture("Background/background.png");
    
    Character player("Character/character.png", 16, 16, 0, 1, 1, windowWidth / 2 - (16 * 6), windowHeight - (16 * 6));

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime(); // Time since last frame

        BeginDrawing();
        ClearBackground(WHITE);

        // Draw background
        DrawTextureEx(background, {0, 0}, 0.0f, 1.0f, WHITE);

        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_A)) {
        // walk
        player.spriteRow = 2;
        player.spriteCount = 4;
        player.spritesPerSecond = 3;
        player.facingLeft = IsKeyDown(KEY_A);
        player.idleTimer = 0.0;
        } 
        else{
        //stand
        player.spriteRow = 0;
        player.spriteCount = 1;
        player.spritesPerSecond = 1;

        player.idleTimer += deltaTime;  
            if (player.idleTimer>=3.0f) {
            //idle
            player.spriteRow = 0;
            player.spriteCount = 26;
            player.spritesPerSecond = 5;
            }
        }

    player.move(deltaTime);
    player.draw();
    DrawText(TextFormat("FT: %08i", (int)GetTime()), 0, 220, 20, BLACK);

        EndDrawing();
    }

    // Unload textures
    UnloadTexture(background);
    CloseWindow();
}
