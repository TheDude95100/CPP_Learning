#include "raylib.h"

struct AnimData{
        Rectangle rec;
        Vector2 pos;
        int frame;
        float updateTime;
        float runningTime;
};

int main()
{
        const int windowHeight{512};
        const int windowWidth{380};

        InitWindow(windowWidth, windowHeight, "Dasher");

        // obstacles
        Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

        int nebVel{-200};



        // Should be a proper class btw
        Texture2D scarfy = LoadTexture("textures/scarfy.png");
        AnimData scarfyData{{0.0, 0.0, scarfy.width / 6, scarfy.height},{ windowWidth /2 - scarfy.width / 12, windowHeight - scarfy.height},0,1.0/12.0,0.0};



        const int gravity{1000};

        bool isInAir{};

        const int jumpVel{-600};

        int velocity{0};

        AnimData nebulae[3]{};

        for(int i =0; i <3;i++){
                nebulae[i] = {{0.0, 0.0, nebula.width / 8, nebula.height / 8},{windowWidth + i*300, windowHeight - nebula.height / 8},0,1.0/12.0,0.0};
        }

        SetTargetFPS(60);
        while (!WindowShouldClose())
        {
                const float dT{GetFrameTime()};
                BeginDrawing();
                ClearBackground(WHITE);

                if (scarfyData.pos.y >= windowHeight - scarfyData.rec.height)
                {
                        velocity = 0;
                        isInAir = false;
                }
                else
                {
                        velocity += gravity * dT;
                }
                if (IsKeyPressed(KEY_SPACE) && !isInAir)
                {
                        velocity += jumpVel;
                        isInAir = true;
                }

                scarfyData.pos.y += velocity * dT;
                scarfyData.runningTime += dT;
                // scarfy's
                if (!isInAir)
                {
                        if (scarfyData.runningTime >= scarfyData.updateTime)
                        {
                                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                                scarfyData.frame++;
                                scarfyData.runningTime = 0.0;
                                if (scarfyData.frame > 5)
                                {
                                        scarfyData.frame = 0;
                                }
                        }
                }

                // nebula's
                for(int i =0; i < 3;i++){
                        nebulae[i].pos.x += nebVel * dT;
                        nebulae[i].runningTime+=dT;
                        if(nebulae[i].runningTime >= nebulae[i].updateTime)
                        {
                                nebulae[i].runningTime = 0.0;
                                nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
                                nebulae[i].frame++;
                                if (nebulae[i].frame > 7)
                                {
                                        nebulae[i].frame = 0;
                                }    
                        }
                        DrawTextureRec(nebula,nebulae[i].rec, nebulae[i].pos, WHITE);
                }
                // Character Draw
                DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
                EndDrawing();
        }
        UnloadTexture(scarfy);
        UnloadTexture(nebula);
        CloseWindow();
}