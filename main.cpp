#include "raylib.h"
#include "Character.h"

int main()
{
    const int windowWidth = 540;
    const int windowHeight = 960;
    InitWindow(windowWidth, windowHeight, "JumpJump");
    InitAudioDevice();

    // Load Sky Texture
    Texture2D sky = LoadTexture("Background/PNG/Game_Background_1/Layers/sky.png");

    // Load sides Texture
    Texture2D sides = LoadTexture("Background/PNG/Game_Background_1/Layers/sides.png");

    // Load Ground Texture
    Texture2D Ground = LoadTexture("Background/PNG/Game_Background_1/Layers/Ground.png");

    // Load Decor Texture
    Texture2D Decor = LoadTexture("Background/PNG/Game_Background_1/Layers/Decor.png");

    // Load Clouds Texture
    Texture2D Clouds = LoadTexture("Background/PNG/Game_Background_1/Layers/Clouds.png");

    // Load Background Texture
    Texture2D BackGround = LoadTexture("Background/PNG/Game_Background_1/Layers/BackGround.png");

    // Load jump sounds
    Sound jumpSounds[7];
    jumpSounds[0] = LoadSound("JumpSounds/sound1.wav");
    jumpSounds[1] = LoadSound("JumpSounds/sound2.wav");
    jumpSounds[2] = LoadSound("JumpSounds/sound3.wav");
    jumpSounds[3] = LoadSound("JumpSounds/sound4.wav");
    jumpSounds[4] = LoadSound("JumpSounds/sound5.wav");
    jumpSounds[5] = LoadSound("JumpSounds/sound6.wav");
    jumpSounds[6] = LoadSound("JumpSounds/sound7.wav");

    Character player("Character/character.png", 16, 16, 0, 1, 1, windowWidth / 2 - (16 * 4), windowHeight / 2 - (16 * 4), 6.0f, false);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime(); // Time since last frame

        BeginDrawing();
        ClearBackground(WHITE);

    // adding jump sounds
    if (IsKeyPressed(KEY_SPACE)) {
    int randomIndex = GetRandomValue(0, 5);
    PlaySound(jumpSounds[randomIndex]);
    }
        float bgY;

        Vector2 bgPos1 = {0.0f, bgY};
        Vector2 bgPos2 = {0.0f, bgY - sky.height};

        // Draw sky
        DrawTextureEx(sky, bgPos1, 0.0f, 1.0f, WHITE);
        DrawTextureEx(sky, bgPos2, 0.0f, 1.0f, WHITE);

        // Draw Clouds
        DrawTextureEx(Clouds, bgPos1, 0.0f, 1.0f, WHITE);
        DrawTextureEx(Clouds, bgPos2, 0.0f, 1.0f, WHITE);

        // Draw BackGround
        DrawTextureEx(BackGround, {0.0,0.0}, 0.0f, 1.0f, WHITE);
        DrawTextureEx(BackGround, {0.0,0.0}, 0.0f, 1.0f, WHITE);

        // Draw Ground
        DrawTextureEx(Ground, {0.0,0.0}, 0.0f, 1.0f, WHITE);
        DrawTextureEx(Ground, {0.0,0.0}, 0.0f, 1.0f, WHITE);

        // Draw sides
        DrawTextureEx(sides, bgPos1, 0.0f, 1.0f, WHITE);
        DrawTextureEx(sides, bgPos2, 0.0f, 1.0f, WHITE);

        // Draw Decor
        DrawTextureEx(Decor, bgPos1, 0.0f, 1.0f, WHITE);
        DrawTextureEx(Decor, bgPos2, 0.0f, 1.0f, WHITE);

        if (IsKeyDown(KEY_D) && !player.isJumping || IsKeyDown(KEY_A) && !player.isJumping)
        {
            // walk
            player.spriteRow = 2;
            player.spriteCount = 4;
            player.spritesPerSecond = 3;
            player.facingLeft = IsKeyDown(KEY_A);
            player.idleTimer = 0.0;
        }
        else if (player.isJumping)
        {
            // jump
            player.spriteRow = 5;
            player.spriteCount = 1;
            player.facingLeft = IsKeyDown(KEY_A);
            player.idleTimer = 0.0;
        }
        else
        {
            // stand
            player.spriteRow = 0;
            player.spriteCount = 1;
            player.idleTimer += deltaTime;
            if (player.idleTimer >= 3.0f)
            {
                // idle
                player.spriteRow = 0;
                player.spriteCount = 26;
                player.spritesPerSecond = 5;
            }
        }

        player.move(deltaTime, windowWidth);
        player.jump(deltaTime, windowHeight);
        player.draw();
        DrawText(TextFormat("Test1: %08i", (int)GetTime()), 20, 220, 20, BLACK);

        EndDrawing();
    }

    // Unload textures
    UnloadTexture(sky);
    UnloadTexture(sides);
    UnloadTexture(Ground);
    UnloadTexture(Decor);
    UnloadTexture(Clouds);
    UnloadTexture(BackGround);

    // Unload sound
    UnloadSound(jumpSounds[0]);
    UnloadSound(jumpSounds[1]);
    UnloadSound(jumpSounds[2]);
    UnloadSound(jumpSounds[3]);
    UnloadSound(jumpSounds[4]);
    UnloadSound(jumpSounds[5]);
    UnloadSound(jumpSounds[6]);

    CloseWindow();
}
