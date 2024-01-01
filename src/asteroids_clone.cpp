#include "../headers/asteroids_clone.hpp"


Object::Object(Texture2D texture, std::string color, float scale = 1.0, Vector2 vector, Vector2 position, int speed) : texture(texture), color(color), scale(scale), vector(vector), position(position), speed(speed)
{
    this->health = 100;
    this->acceleration = 0;
    this->dec_factor = 0.9; 
    this->hitbox = {this->position.x, this->position.y, (float)this->texture.width, (float)this->texture.height};
}
Rectangle Object::getHitBox()
{
    return this->hitbox;
}
int Object::getHealth()
{
    return this->health;
}
void Object::setHealth(int health_new)
{
    this->health = health_new;
}
std::string Object::getColor()
{
    return this->color;
}
Vector2 Object::getVector()
{
    return this->vector;
}
void Object::setVector(Vector2 vector_new)
{
    this->vector = vector_new;
}
void Object::rotate(int angle)
{
    this->vector = Vector2Rotate(this->vector, DEG2RAD * (float)angle );
}
void Object::drift()
{
    this->position = Vector2Add(this->position, Vector2Scale(this->vector, this->speed));
}
void Object::decelerate()
{
    this->speed = this->speed * dec_factor;
}
bool Object::doRectIntersect(Rectangle rectangle1, Rectangle rectangle2)
{
    float x1 = rectangle1.x; 
    float y1 = rectangle1.y;
    float w1 = rectangle1.width;
    float h1 = rectangle1.height;
    float x2 = rectangle2.x; 
    float y2 = rectangle2.y; 
    float w2 = rectangle2.width;
    float h2 = rectangle2.height;
    if((x1 >= x2) && (x1 <=( x2 + w2)))
    {
        if( (y1 >= y2) && (y1 <= (y2 + h2)))
            return true;
    }   
    else if(((x1 + w1) >= x2) && ((x1 + w1) <=( x2 + w2)))
    {
        if((y1 >= y2) && (y1 <= (y2 + h2)))
            return true;
    }
    else if((x1 >= x2) && (x1 <=( x2 + w2)))
    {
        if( ((y1 + h1) >= y2) & ((y1 + h1) <= (y2 + h2)))
            return true;
    }     
    else if(((x1 + w1) >= x2) && ((x1 + w1) <=( x2 + w2)))
    {
        if( ((y1 + h1) >= y2) && ((y1 + h1) <= (y2 + h2)))
            return true;
    }  
    else
        return false;
}
bool Object::isthereCrash(Object object)
{
    return this->doRectIntersect(this->hitbox, object.getHitBox());
}


