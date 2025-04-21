#include "raylib.h"
int main()
{
    int width {1920};
    int height{1080};
    InitWindow(width,height,"EREN JAGER");
    int circle_x = width/2;
    int circle_y = height/2;
    int circle_radius = width/16;
    int l_circle_x{circle_x - circle_radius};
    int r_circle_x{circle_x + circle_radius};
    int u_circle_y{circle_y - circle_radius};
    int b_circle_y{circle_y + circle_radius};

    int axe_x{300};
    int axe_y{0};
    int axe_size{50};
    int l_axe_x{axe_x};
    int r_axe_x{axe_x + axe_size};
    int u_axe_y{axe_y};
    int b_axe_y{axe_y + axe_size};
    

    int direction{10};


    bool collision_with_axe = 
                            (b_axe_y >= u_circle_y) && 
                            (u_axe_y <= b_circle_y) && 
                            (l_axe_x <= r_circle_x) && 
                            (r_axe_x >= l_circle_x);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        l_circle_x = circle_x - circle_radius;
        r_circle_x = circle_x + circle_radius;
        u_circle_y = circle_y - circle_radius;
        b_circle_y = circle_y + circle_radius;

        l_axe_x = axe_x;
        r_axe_x = axe_x + axe_size;
        u_axe_y = axe_y;
        b_axe_y = axe_y + axe_size;

        collision_with_axe = 
                            (b_axe_y >= u_circle_y) && 
                            (u_axe_y <= b_circle_y) && 
                            (l_axe_x <= r_circle_x) && 
                            (r_axe_x >= l_circle_x);

        BeginDrawing();
        ClearBackground(WHITE);
        if(collision_with_axe)
        {
            DrawText("Game Over!", width/2,height/2, 50, RED);
        }
        else
        {
            DrawCircle(circle_x, circle_y, circle_radius, BLUE);
            DrawRectangle(axe_x,axe_y,axe_size,axe_size,RED);

            axe_y+=direction;
            if(axe_y > height - axe_size || axe_y < 0){
                direction = -direction;
            }
            if(IsKeyDown(KEY_D) && circle_x < width - circle_radius){
                circle_x+=10;
            }
            if(IsKeyDown(KEY_A) && circle_x > 0 + circle_radius){
                circle_x-=10;
            }
        }
        EndDrawing();
    }
}