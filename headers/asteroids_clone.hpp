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
    Vector2 vector;
    Vector2 position;
    int speed;
    float dec_factor; 
    int acceleration;
    public:
    Object(Texture2D texture, std::string color, float scale, Vector2 vector, Vector2 position, int speed ); 
    Rectangle getHitBox();
    int getHealth();
    void setHealth(int health_new);
    std::string getColor();
    Vector2 getVector();
    void setVector(Vector2 vector_new);
    void rotate(int angle);
    void drift();
    void decelerate();
    bool doRectIntersect(Rectangle rectangle1, Rectangle rectangle2);
    bool isthereCrash(Object object);
  };
  class Ship: public Object
{
    private: 
    int deaths;
    public:
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
