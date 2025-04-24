#include "raylib.h"
int main(){
    const int windowHeight{1080};
    const int windowWidth{1920};

    InitWindow(windowWidth,windowHeight,"Dasher");

    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    const int gravity{1};

    bool isInAir{};

    const int jumpVel{-22};

    int velocity{0};

    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);

        if(scarfyPos.y >= windowHeight - scarfyRec.height)
        {
                velocity = 0;
                isInAir = false;
        }
        else 
        {
                velocity += gravity;
        }
        if(IsKeyPressed(KEY_SPACE) && !isInAir)
        {
                velocity += jumpVel;
                isInAir = true;
        }
        scarfyPos.y += velocity;
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
        EndDrawing();
    }
    CloseWindow();
}