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
    std::string color;
    float scale;
    const int screenWidth;
    const int screenHeight;
    Vector2 vector;
    Vector2 position;
    float rotation;
    float speed;
    float dec_factor; 
    public:
    Object(Texture2D texture, std::string color, float scale, const int screenWidth, const int screenHeight, float speed); 
    Texture2D getTexture();
    Rectangle getHitBox();
    Rectangle getDestRec();
    int getHealth();
    void setHealth(int health_new);
    std::string getColor();
    Vector2 getVector();
    void setVector(Vector2 vector_new);
    Vector2 getPosition();
    Vector2 getOrigin();
    void rotate(float angle); // in deg
    float getRotation();
    void drift();
    void decelerate();
    bool doRectIntersect(Rectangle rectangle1, Rectangle rectangle2);
    bool isthereCrash(Object object);
    void setSpeed(float s);

  };
  class Ship: public Object
{
    private: 
    int deaths;
    public:
    Ship(Texture2D texture, std::string color, float scale, const int screenWidth, const int screenHeight, float speed);
    void move();
    void shoot();
    void accelerate();
    int getDeaths();
    int incrementDeaths();
};
class Asteroid: public Object
{
  public:
  void split();
};
