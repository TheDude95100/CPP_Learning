#include "raylib.h"
int main(){
    const int windowHeight{1080};
    const int windowWidth{1920};

    InitWindow(windowWidth,windowHeight,"Dasher");

    const int width{50};
    const int height{80};

    const int gravity{1};

    bool isInAir{};

    const int jumpVel{-22};

    int posY{windowHeight - height};
    int velocity{0};

    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);

        if(posY >= windowHeight - height)
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
        posY += velocity;
        DrawRectangle(windowWidth/2, posY, width,height,RED);
        EndDrawing();
    }
    CloseWindow();
}