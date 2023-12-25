/*******************************************************************************************
*
*   raylib [textures] example - Texture source and destination rectangles
*
*   This example has been created using raylib 1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"
#include  <stdlib.h>
#include <iostream>
#include <time.h>       /* time */
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
 
    const int screenWidth = 1000;
    const int screenHeight = 500;
    /* initialize random seed: */
    srand(time(NULL));
    InitWindow(screenWidth, screenHeight, "raylib [textures] examples - texture source and destination rectangles");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)

    Texture2D ship = LoadTexture("resources/futurama_ship_bw.png");        // Texture loading
    Texture2D meteor = LoadTexture("resources/large_metor.png");        // Load metor

    int frameWidth = ship.width;
    int frameHeight = ship.height;

    // Source rectangle (part of the texture to use for drawing)
    Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };
    Rectangle sourceRec_meteor = { 0.0f, 0.0f, (float)meteor.width, (float)meteor.height };
    // Destination rectangle (screen rectangle where drawing part of texture)
    Rectangle destRec = { screenWidth/2.0f ,screenHeight/2.0f,  frameWidth, frameHeight };
    Rectangle destRec_meteor = { rand() % (screenWidth + 1)   ,rand() % (screenHeight + 1),  meteor.width, meteor.height };
    Vector2 ship_reference_pt = { destRec.x, destRec.y };
    // Origin of the texture (rotation/scale point), it's relative to destination rectangle size
   // Vector2 origin = { screenWidth / 2.0f - frameWidth / 2.0f, screenHeight / 2.0f - frameHeight  /2.0f };
    Vector2 origin = { frameWidth/2.0f , frameHeight / 2.0f };
    Vector2 origin_1 = origin;
    Vector2 origin_meteor = { meteor.width / 2.0f , meteor.height / 2.0f };
    Vector2 unit_vector = { 1.0f, 0.0f };
    Vector2 ship_vector = { 1.0f, 0.0f };
    int framesCounter = 0;  
    int framesSpeed = 8;
    int rotation = 0;
    int rotation_meteor = 0;
    int accelerate = 0;
    float velocity = 2.0f;
    int f_0 = 0;
    float deceleration_f = 0.90; // Deceleration factor to be multipied with velocity every second
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        framesCounter++;
        rotation_meteor += 5;

        if (IsKeyDown(KEY_UP)) 
        {
            accelerate = 1;
            f_0 = framesCounter;
            velocity = 2.0f;
       
        } 
        if (IsKeyDown(KEY_RIGHT))
        {

            if (rotation == 355)
            {
                rotation = 0;
            }
            else rotation += 5;
            ship_vector = Vector2Rotate(unit_vector, DEG2RAD * (float)rotation );

        }; 
        if (IsKeyDown(KEY_LEFT))
        {

            if (rotation == 5)
            {
                rotation = 355;
            }
            else rotation -= 5;
            ship_vector = Vector2Rotate(unit_vector, DEG2RAD * (float)rotation);

        };
        if (accelerate == 1)
        {
            if ((framesCounter - f_0)  == 60)
            {
                f_0 = framesCounter;
                if (velocity > 0.1f)
                {
                    velocity = velocity*deceleration_f;
                }
                else
                {
                    accelerate = 0;
                    velocity = 0.1f;
                }
                
            }
            ship_reference_pt = Vector2Add(ship_reference_pt, Vector2Scale(ship_vector, velocity));
        }
        if (ship_reference_pt.x > screenWidth )
            ship_reference_pt.x = 0;
        if (ship_reference_pt.x < 0)
            ship_reference_pt.x = screenWidth;
        if (ship_reference_pt.y > screenHeight)
            ship_reference_pt.y = 0;
        if (ship_reference_pt.y < 0)
            ship_reference_pt.y = screenHeight;
        destRec.x = ship_reference_pt.x;
        destRec.y = ship_reference_pt.y;
       /*
        if (IsKeyDown(KEY_D)) origin.x = origin.x + 2.0f;
        if (IsKeyDown(KEY_A)) origin.x = origin.x - 2.0f;
        if (IsKeyDown(KEY_W)) origin.y = origin.y - 2.0f;
        if (IsKeyDown(KEY_S)) origin.y = origin.y + 2.0f;
    */
        
       origin_1.x = destRec.x;
       origin_1.y = destRec.y;

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // NOTE: Using DrawTexturePro() we can easily rotate and scale the part of the texture we draw
        // sourceRec defines the part of the texture we use for drawing
        // destRec defines the rectangle where our texture part will fit (scaling it to fit)
        // origin defines the point of the texture used as reference for rotation and scaling
        // rotation defines the texture rotation (using origin as rotation point)
        DrawTexturePro(ship, sourceRec, destRec, origin, (float)rotation, GREEN);
        DrawTexturePro(meteor, sourceRec_meteor, destRec_meteor, origin_meteor, (float)rotation_meteor, GREEN);
        //DrawTexture(ship, origin_1.x, origin_1.y, WHITE);
        DrawPixel( 10, 10, RED);
        DrawLine((int)destRec.x, 0, (int)destRec.x, screenHeight, GRAY);
       // DrawRectangle(destRec.x+ 10, destRec.y + 10, destRec.width + 10, destRec.height + 10, PURPLE);
        DrawLine(0, 0, 0, screenHeight, BLUE);
        
        DrawText(TextFormat("Coordinates of Ship Origin: %lf, %lf",origin.x,origin.y), origin.x, origin.y, 15, GRAY);
        DrawText(TextFormat("Rotation:  %i", rotation), screenWidth - 700, screenHeight -250, 15, GRAY);
        DrawText(TextFormat("Velocity:  %lf", velocity), screenWidth - 700, screenHeight - 230, 15, GRAY);
        DrawText(TextFormat("Ship Vector Angle:  %lf",RAD2DEG *  Vector2Angle( ship_vector, unit_vector)), screenWidth - 700, screenHeight - 270, 15, GRAY);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(ship);        // Texture unloading

    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}