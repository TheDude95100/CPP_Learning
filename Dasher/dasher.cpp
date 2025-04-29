#include "raylib.h"

struct AnimData{
        Rectangle rec;
        Vector2 pos;
        int frame;
        float updateTime;
        float runningTime;
};

AnimData updateAnimeData(AnimData data, float deltaTime, int maxFrame){
        data.runningTime+=deltaTime;
        if(data.runningTime >= data.updateTime)
        {
                data.runningTime = 0.0;
                data.rec.x = data.frame * data.rec.width;
                data.frame++;
                if (data.frame > maxFrame)
                {
                        data.frame = 0;
                }    
        }
        return data;
}

void DrawBackground(float* bgX, float dT, Texture2D background,int scale){
        *bgX -= 20*dT;
        if(*bgX <= -background.width*scale){
                *bgX = 0.0;
        }
        Vector2 bg1Pos{*bgX,0.0};
        DrawTextureEx(background,bg1Pos,0.0,scale,WHITE);
        Vector2 bg2Pos{*bgX + background.width *scale, 0.0};
        DrawTextureEx(background,bg2Pos,0.0,scale,WHITE);
}
int main()
{
        const int windowHeight{380};
        const int windowWidth{512};

        const int numberOfNebula{3};

        InitWindow(windowWidth, windowHeight, "Dasher");

        // obstacles
        Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

        int nebVel{-200};


        // Should be a proper class btw
        Texture2D scarfy = LoadTexture("textures/scarfy.png");
        AnimData scarfyData{{0.0, 0.0, scarfy.width / 6, scarfy.height},{ windowWidth /2 - scarfy.width / 12, windowHeight - scarfy.height},0,1.0/8.0,0.0};



        const int gravity{1000};

        bool isInAir{};

        const int jumpVel{-600};

        int velocity{0};

        Texture2D background = LoadTexture("textures/far-buildings.png");
        Texture2D buildings = LoadTexture("textures/back-buildings.png");
        Texture2D foreground = LoadTexture("textures/foreground.png");

        AnimData nebulae[numberOfNebula]{};

        for(int i =0; i <numberOfNebula;i++){
                nebulae[i] = {{0.0, 0.0, nebula.width / 8, nebula.height / 8},{windowWidth + i*300, windowHeight - nebula.height / 8},0,1.0/12.0,0.0};
        }

        SetTargetFPS(60);
        float bgX{0};
        while (!WindowShouldClose())
        {
                const float dT{GetFrameTime()};
                BeginDrawing();
                ClearBackground(WHITE);
                DrawBackground(&bgX,dT,background,2.0);

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
                        scarfyData = updateAnimeData(scarfyData, dT,5);
                }

                // nebula's
                for(int i =0; i < numberOfNebula;i++){
                        nebulae[i].pos.x += nebVel * dT;
                        nebulae[i] = updateAnimeData(nebulae[i], dT, 7);
                        DrawTextureRec(nebula,nebulae[i].rec, nebulae[i].pos, WHITE);
                }
                // Character Draw
                DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
                EndDrawing();
        }
        UnloadTexture(scarfy);
        UnloadTexture(nebula);
        UnloadTexture(background);
        UnloadTexture(buildings);
        UnloadTexture(foreground);
        CloseWindow();
}