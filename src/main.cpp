#include "../headers/asteroids_clone.hpp"
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1500;
    const int screenHeight = 800;
InitWindow(screenWidth, screenHeight, "Asteroids");
Ship ship(LoadTexture("resources/futurama_ship_bw.png"), GREEN, 1.0, screenWidth, screenHeight , 2.0, LoadTexture("resources/beam.png"));
int size = rand() % 15 + 5;
Asteroid* asteroids = new Asteroid[size];
for(int i = 0; i < size; i++)
{
    asteroids[i] = Asteroid(LoadTexture("resources/large_meteor.png"), WHITE, float(rand() % 500)/100, screenWidth, screenHeight , 2.0);
}

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
            ship.rotate_to_right();
        if (IsKeyDown(KEY_LEFT))
            ship.rotate_to_left();
         if (IsKeyDown(KEY_SPACE)) 
        {
           ship.shoot();
        } 
        ship.drift();
        for(int i = 0; i < size; i++)
        {
            asteroids[i].drift();
        }
        ship.drift_beams();
        ship.decelerate();
       
       // DrawRectangle(destRec.x+ 10, destRec.y + 10, destRec.width + 10, destRec.height + 10, PURPLE);
        DrawLine(0, 0, 0, screenHeight, BLUE);
        
         DrawText(TextFormat("Coordinates of Ship Origin: %lf, %lf",ship.getPosition().x,ship.getPosition().y),500, 250, 15, GRAY);
        DrawText(TextFormat("Ship vector: %lf, %lf",ship.getVector().x,ship.getVector().y),500, 280, 15, GRAY);
         DrawText(TextFormat("Number of beams: %ld",ship.getNumBeams()),500, 300, 15, GRAY);
         
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
    // Deallocate memory
    delete[] asteroids;
    return 0;
}