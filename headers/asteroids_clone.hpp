#pragma once
#include "raylib.h"
#include "raymath.h"
#include <string>
class Object 
  {  
    private:
    Texture2D texture;
    Rectangle hitbox; 
    int health;
    Color color;
    float scale;
    int screenWidth;
    int screenHeight;
    Vector2 vector;
    Vector2 position;
    float rotation;
    float speed;
    float dec_factor; 
    public:
    Object(Texture2D texture, Color color, float scale, int screenWidth, int screenHeight, float speed); 
    Object(); 
    Texture2D getTexture();
    int getScreenWidth();
    int getScreenHeight();
    Rectangle getHitBox();
    Rectangle getDestRec();
    int getHealth();
    void setHealth(int health_new);
    Color getColor();
    Vector2 getVector();
    void setVector(Vector2 vector_new);
    void setPosition(Vector2 pos);
    Vector2 getPosition();
    Vector2 getOrigin();
    void rotate_to_right(); 
    void rotate_to_left();
    float getRotation();
    void drift();
    void decelerate();
    bool doRectIntersect(Rectangle rectangle1, Rectangle rectangle2);
    bool isthereCrash(Object object);
    bool outofBounds();
    bool outLeft();
    bool outRight();
    bool outDown();
    bool outUp();
    float getSpeed();
    void setSpeed(float s);

  };
  class Ship: public Object
{
    private: 
    int deaths;
    Texture2D beam_sprite;
    Object beams[30];
    int number_of_beams;
    int max_num_beams;
    public:
    Ship(Texture2D texture, Color color, float scale, int screenWidth, int screenHeight, float speed, Texture2D beam_sprite);
    void move();
    void shoot();
    void accelerate();
    int getDeaths();
    int incrementDeaths();
    void drift_beams();
    int getNumBeams();

};
class Asteroid: public Object
{
  public:
  Asteroid(Texture2D texture, Color color, float scale, const int screenWidth, const int screenHeight, float speed);
  void split();
};
