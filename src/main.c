#include "raylib.h"
#include <stdio.h>
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Shift");
    
    Rectangle mainSqaure = { 535.0, 115.0, 850.0, 850.0};
    Rectangle player = { 650, 280, 40, 40 };
    
    Camera2D camera = { 0 };
    camera.target = (Vector2){ mainSqaure.x + 425, mainSqaure.y + 425 };
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    //camera.offset = (Vector2){ 425.0f, 425.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(144);               // Set our game to run at 144 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        //float deltaTime = GetFrameTime();
        
        //left and right collisions
        if (player.x <= mainSqaure.x) player.x = mainSqaure.x;
        else if (player.x + player.width >= mainSqaure.x + mainSqaure.width) player.x = (mainSqaure.x + mainSqaure.width)- player.width;

        ///up and down collisions
        if (player.y <= mainSqaure.y) player.y = mainSqaure.y;
        else if (player.y + player.height >= mainSqaure.y + mainSqaure.height) player.y = (mainSqaure.y + mainSqaure.height) - player.height;
        
        //align camera
        camera.target = (Vector2){ mainSqaure.x + 425, mainSqaure.y + 425};
        
        //possibly temp camera rotation controls
        if (IsKeyDown(KEY_A)) camera.rotation--;
        else if (IsKeyDown(KEY_S)) camera.rotation++;
        
        //possibly temp rotation lock
        if (camera.rotation > 180) camera.rotation = 180;
        else if (camera.rotation < -180) camera.rotation = -180;
        
        /* temp player movement controls
        if (IsKeyDown(KEY_RIGHT)) player.x += 2.0f;
        if (IsKeyDown(KEY_LEFT)) player.x -= 2.0f;
        if (IsKeyDown(KEY_UP)) player.y -= 2.0f;
        if (IsKeyDown(KEY_DOWN)) player.y += 2.0f;
        */
        
        //trying to figure out how to apply gravity based on camera rotation
        switch((int)camera.rotation){
        case -180:
        player.y -= 5;
        case -90:
        player.x -= 5;
        case 0:
        player.y -= 5;
        case 90:
        player.x += 5;
        case 180:
        player.y -= 5;
        }
        
        
        
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            
            BeginMode2D(camera);
            
            DrawRectangleRec(mainSqaure, DARKGRAY); 
            
            DrawRectangleRec(player, RED);
            
            EndMode2D();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
