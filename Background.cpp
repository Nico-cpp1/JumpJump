#include "Background.h"

Background::Background(const char *texture_sky, const char *texture_sides, const char *texture_ground, const char *texture_decor, const char *texture_clouds, const char *texture_background, float bgY1) {
    sky = LoadTexture(texture_sky);
    sides = LoadTexture(texture_sides);
    ground = LoadTexture(texture_ground);
    decor = LoadTexture(texture_decor);
    clouds = LoadTexture(texture_clouds);
    backGround = LoadTexture(texture_background);
    this->bgY1 = bgY1;
}

void Background::draw(int windowHeight)
{    
    // Draw sky
    DrawTextureEx(sky, {0.0, bgY1}, 0.0f, 1.0f, WHITE);
    DrawTextureEx(sky, {0.0, bgY1-windowHeight}, 0.0f, 1.0f, WHITE);

    // Draw Clouds
    DrawTextureEx(clouds, {0.0, bgY1}, 0.0f, 1.0f, WHITE);
    DrawTextureEx(clouds, {0.0, bgY1-windowHeight}, 0.0f, 1.0f, WHITE);

    // Draw BackGround
    DrawTextureEx(backGround, {0.0, 0.0}, 0.0f, 1.0f, WHITE);
    DrawTextureEx(backGround, {0.0, 0.0}, 0.0f, 1.0f, WHITE);

    // Draw Ground
    DrawTextureEx(ground, {0.0, 0.0}, 0.0f, 1.0f, WHITE);
    DrawTextureEx(ground, {0.0, 0.0}, 0.0f, 1.0f, WHITE);

    // Draw sides
    DrawTextureEx(sides, {0.0, bgY1}, 0.0f, 1.0f, WHITE);
    DrawTextureEx(sides, {0.0, bgY1-windowHeight}, 0.0f, 1.0f, WHITE);
}

void Background::drawDecor(int windowHeight) {

    // Draw Decor
    DrawTextureEx(decor, {0.0, bgY1}, 0.0f, 1.0f, WHITE);
    DrawTextureEx(decor, {0.0, bgY1-windowHeight}, 0.0f, 1.0f, WHITE);
}

void Background::unload()
{
    UnloadTexture(sky);
    UnloadTexture(sides);
    UnloadTexture(ground);
    UnloadTexture(decor);
    UnloadTexture(clouds);
    UnloadTexture(backGround);
}