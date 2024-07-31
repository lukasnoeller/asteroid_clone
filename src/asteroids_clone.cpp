#include "../headers/asteroids_clone.hpp"


Object::Object(Texture2D texture, std::string color, float scale , const int screenWidth, const int screenHeight, float speed) : texture(texture), color(color), scale(scale), screenWidth(screenWidth), screenHeight(screenHeight), speed(speed)
{
    this->health = 100;
    this->dec_factor = 0.994f;
    this->vector = { 1.0f , 0.0f };
    this->position =  { this->screenWidth / 2.0f , this->screenHeight / 2.0f };
    this->rotation = 0.0f;
    this->hitbox = {0.0f, 0.0f, (float)this->texture.width, (float)this->texture.height};
}

Texture2D Object::getTexture()
{
    return this->texture;
}
Rectangle Object::getHitBox()
{
    return this->hitbox;
}
Rectangle Object::getDestRec()
{
    Rectangle destRec = { this->position.x , this->position.y,   this->texture.width, this->texture.height };
    return destRec;
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
Vector2 Object::getPosition()
{
    return this->position;
}
Vector2 Object::getOrigin()
{
    float width  = this->texture.width;
    float height = this->texture.height;
    Vector2 origin;
    origin = { width / 2.0f, height / 2.0f};
    return origin;

}
void Object::rotate(float angle)
{
    this->rotation =  angle;
    this->vector.x = cos( DEG2RAD * rotation);
    this->vector.y = sin( DEG2RAD * rotation);
}
float Object::getRotation()
{
    return this->rotation;
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
void Object::setSpeed(float s)
{
    this->speed = s;
}
Ship::Ship(Texture2D texture, std::string color, float scale, const int screenWidth, const int screenHeight, float speed) : Object(texture, color, scale, screenWidth, screenHeight, speed)
{
    this->deaths = 0;
}

void Ship::accelerate()
{
    this->setSpeed(2.0f);
}



