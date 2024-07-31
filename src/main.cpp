#include "../headers/asteroids_clone.hpp"
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1500;
    const int screenHeight = 800;
InitWindow(screenWidth, screenHeight, "Asteroids");
Ship ship(LoadTexture("resources/futurama_ship_bw.png"), "green", 1.0, screenWidth, screenHeight , 2.0 ); 
ship.rotate(45);
SetTargetFPS(60);
float angle = 0;
     while (!WindowShouldClose())   
     {    
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
         if (IsKeyDown(KEY_UP)) 
        {
           ship.accelerate();
        } 
        if (IsKeyDown(KEY_RIGHT))
        {
            ship.rotate(angle);
            if (angle == 360)
            {
                angle = 0;
            }
            else angle += 1; 
        };
          if (IsKeyDown(KEY_LEFT))
        {
            ship.rotate(angle);
            if (angle == 0)
            {
                angle = 360;
            }
            else angle -= 1; 
        }; 
 

        
        ship.drift();
        DrawTexturePro(ship.getTexture(), ship.getHitBox(), ship.getDestRec(),ship.getOrigin(), ship.getRotation(), RED);
        ship.decelerate();
        DrawPixel( 10, 10, RED);
       
       // DrawRectangle(destRec.x+ 10, destRec.y + 10, destRec.width + 10, destRec.height + 10, PURPLE);
        DrawLine(0, 0, 0, screenHeight, BLUE);
        
         DrawText(TextFormat("Coordinates of Ship Origin: %lf, %lf",ship.getPosition().x,ship.getPosition().y),500, 250, 15, GRAY);
        DrawText(TextFormat("Ship vecvtor: %lf, %lf",ship.getVector().x,ship.getVector().y),500, 280, 15, GRAY);
         DrawText(TextFormat("Angle: %lf degrees",ship.getRotation()),500, 300, 15, GRAY);
        // DrawText(TextFormat("Rotation:  %i", rotation), screenWidth - 700, screenHeight -250, 15, GRAY);
        // DrawText(TextFormat("Velocity:  %lf", velocity), screenWidth - 700, screenHeight - 230, 15, GRAY);
        // DrawText(TextFormat("Ship Vector Angle:  %lf",RAD2DEG *  Vector2Angle( ship_vector, unit_vector)), screenWidth - 700, screenHeight - 270, 15, GRAY);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
// De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(ship.getTexture());        // Texture unloading

    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}