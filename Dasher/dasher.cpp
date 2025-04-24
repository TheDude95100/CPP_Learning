#include "raylib.h"
int main(){
    const int windowHeight{512};
    const int windowWidth{380};

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

    const int gravity{1000};

    bool isInAir{};

    const int jumpVel{-600};

    int velocity{0};

    SetTargetFPS(60);
    while(!WindowShouldClose()){
        const float dT{GetFrameTime()};
        BeginDrawing();
        ClearBackground(WHITE);

        if(scarfyPos.y >= windowHeight - scarfyRec.height)
        {
                velocity = 0;
                isInAir = false;
        }
        else 
        {
                velocity += gravity * dT;
        }
        if(IsKeyPressed(KEY_SPACE) && !isInAir)
        {
                velocity += jumpVel;
                isInAir = true;
        }
        scarfyPos.y += velocity * dT;
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();
}