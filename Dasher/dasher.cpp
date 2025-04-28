#include "raylib.h"
int main(){
    const int windowHeight{512};
    const int windowWidth{380};

    InitWindow(windowWidth,windowHeight,"Dasher");

    //obstacles
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebRec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 nebPos{windowWidth, windowHeight - nebRec.height};

    int nebVel{-600};

    //Should be a proper class btw
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
    const float updateTime{1.0/12.0};

    float runningTime{0};
    int animFrame{0};
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
        nebPos.x += nebVel *dT;
        scarfyPos.y += velocity * dT;
        runningTime += dT;
        if(!isInAir){
                if(runningTime >= updateTime)
                {
                        scarfyRec.x = animFrame * scarfyRec.width;
                        animFrame ++;
                        runningTime = 0.0;
                        if(animFrame > 5)
                        {
                                animFrame = 0;
                        } 
                }
        }

        //Draw obstacle
        DrawTextureRec(nebula,nebRec, nebPos, WHITE);

        //Character Draw
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}