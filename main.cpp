#include "raylib.h"
#include "Character.h"
#include "Platform.h"
#include "Background.h"

const int windowWidth = 540;
const int windowHeight = 960;
float deathStartTime = 0;
bool isDead = false;
int deaths = 0;

void death(Character &player, int windowWidth, int windowHeight)
{
    if (!isDead)
    {
        deathStartTime = GetTime();
        isDead = true;         
    }

    DrawText("Tot!", windowWidth / 2 - 100, windowHeight / 2, 100, RED);

    int deathTimer = 1 + (int)(GetTime() - deathStartTime);
    if (deathTimer >= 5)
    {
        DrawText("Restart? Press R", player.border + 5, windowHeight / 2 - 100, 45, RED);
        if (IsKeyPressed(KEY_R))
        {
            player.posY = windowHeight / 2 - 50;
            player.posX = windowWidth / 2;
            deathStartTime = 0;
            isDead = false;
            deaths = deaths + 1;
        }
    }
}

void LandOnPlatform(Character &player, Rectangle platform)
{
    Rectangle playerCollisionRec = {
        player.posX + 20,
        player.posY + player.spriteHeight * player.scale - 10,
        player.spriteWidth * player.scale - 40,
        10};
    DrawRectangleLinesEx(playerCollisionRec, 1, RED);
    DrawRectangleLinesEx(platform, 1, RED);
    
    if (CheckCollisionRecs(playerCollisionRec, platform))
    {
        bool fallingDown = player.velocity > 0;
        bool abovePlatform = (player.posY + player.spriteHeight * player.scale - player.velocity) <= platform.y;
        if (fallingDown && abovePlatform)
        {
            player.isJumping = false;
            player.velocity = 0;
            player.posY = platform.y - player.spriteHeight * player.scale;
        }
    }
}

void BackgroundScroll(Character &player, Background &background, Platform* platforms[], int numPlatforms, Platform &platform) {
    float scrollSpeed = 0.0f;

    if (player.posY < windowHeight / 2 - 100) {
        scrollSpeed = +5.0f;
    } else if (player.posY > windowHeight / 2 + 50 && background.bgY1 > 15) {
        scrollSpeed = -15.0f;
        player.posY = background.bgY1+windowHeight;
    }

    background.bgY1 += scrollSpeed;
    
    for (int i = 0; i < numPlatforms; i++) {
        platforms[i]->posY += scrollSpeed;
    }

    platform.posY += scrollSpeed;
}

int main()
{   
    //Timer
    if (deathStartTime == 1) deathStartTime = GetTime();

    InitWindow(windowWidth, windowHeight, "JumpJump");
    InitAudioDevice();

    Character player("Character/character.png", 16, 16, 0, 1, 1, windowWidth / 2, windowHeight / 2 - 13, 6.0f, false);

    Platform platform("Pads/PNG/Pad_1_1.png", windowWidth / 2, windowHeight / 2 + 87, 0.25f, 394 * 0.25f);

    // initialise platforms
    Platform *platforms[10];
    for (int i = 0; i < 10; i++)
    {
        float x = GetRandomValue(player.border + 30, windowWidth - player.border - platform.width - 30);
        float y = windowHeight / 2 - i * 200;
        platforms[i] = new Platform("Pads/PNG/Pad_1_1.png", x, y, 0.25f, platform.width);
    }

    Background background(
        "Background/PNG/Game_Background_1/Layers/sky.png",
        "Background/PNG/Game_Background_1/Layers/sides.png",
        "Background/PNG/Game_Background_1/Layers/Ground.png",
        "Background/PNG/Game_Background_1/Layers/Decor.png",
        "Background/PNG/Game_Background_1/Layers/Clouds.png",
        "Background/PNG/Game_Background_1/Layers/BackGround.png",
        0.0f                                                    );

    /* // Initialize Camera2D
    Camera2D camera = {0};
    camera.offset.y = windowHeight / 2;
    camera.zoom = 1.0f; */

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime(); // Time since last frame

        // Update player
        player.update(deltaTime);
        player.move(deltaTime, windowWidth);
        player.jump(deltaTime, windowHeight);
        BackgroundScroll(player, background, platforms, 10, platform);

        BeginDrawing();
        ClearBackground(WHITE);

        /* // Begin camera mode
        BeginMode2D(camera); */

        // Draw game world
        background.draw(windowHeight);
        platform.draw();

        /* camera.target.x = 0;
        if (player.posY < windowHeight / 2)
        {
            camera.target.y = (float){player.posY};  // Update camera to follow the player
        }
        else if (player.posY -100 > windowHeight/2)
        {   
            camera.target.y = windowHeight/2;
            death(player, windowWidth, windowHeight);
        } */

        // draw platforms
        for (int i = 0; i < 10; i++)
        {
            platforms[i]->draw();
            // collision for platforms
            float x = platforms[i]->posX;
            float y = platforms[i]->posY;
            float width = platforms[i]->texture.width * platforms[i]->scale;
            float height = platforms[i]->texture.height * platforms[i]->scale;

            Rectangle rec = {x, y, width, height};
            LandOnPlatform(player, rec);
        };

        // collision for start platform
        Rectangle platformCollisionRec = {
            platform.posX, platform.posY,
            platform.texture.width * platform.scale,
            platform.texture.height * platform.scale};

        LandOnPlatform(player, platformCollisionRec);

        if (player.posY -100 > windowHeight/2) {
            death(player, windowWidth, windowHeight);
        }

        player.draw();
        background.drawDecor(windowHeight);

        /* // End camera mode
        EndMode2D(); */

        DrawText(TextFormat("Time: %02i", (int)GetTime()), 20, 30, 20, GRAY);
        DrawText(TextFormat("deaths: %02i", deaths), 20, 50, 20, GRAY);

        EndDrawing();
    }

    // Unload textures and sounds
    background.unload();
    player.unload();
    platform.unload();

    CloseWindow();
}
