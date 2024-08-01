#include "../headers/asteroids_clone.hpp"


Object::Object(Texture2D texture, Color color, float scale , int screenWidth, int screenHeight, float speed) : texture(texture), color(color), scale(scale), screenWidth(screenWidth), screenHeight(screenHeight), speed(speed)
{
    this->health = 100;
    this->dec_factor = 0.994f;
    this->vector = { 1.0f , 0.0f };
    this->position =  { this->screenWidth / 2.0f , this->screenHeight / 2.0f };
    this->rotation = 0.0f;
    this->hitbox = {0.0f, 0.0f, (float)(this->texture.width) , (float)(this->texture.height) };
}
Object::Object() : health(0), dec_factor(0.0f), vector({0.0f, 0.0f}), position({0.0f, 0.0f}), rotation(0.0f),
        hitbox({0.0f, 0.0f, 0.0f, 0.0f}), screenHeight(0), screenWidth(0) {}

Texture2D Object::getTexture()
{
    return this->texture;
}
int Object::getScreenWidth()
{
    return this->screenWidth;
}
int Object::getScreenHeight()
{
    return this->screenHeight;
}
Rectangle Object::getHitBox()
{
    return this->hitbox;
}
Rectangle Object::getDestRec()
{
    Rectangle destRec = { this->position.x , this->position.y, (float)(this->texture.width) * this->scale, (float)(this->texture.height) * this->scale };
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
Color Object::getColor()
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
void Object::setPosition(Vector2 pos)
{
    this->position = pos;
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
void Object::rotate_to_right()
{
    
    this->vector.x = cos( DEG2RAD * this->rotation);
    this->vector.y = sin( DEG2RAD * this->rotation);
    if (this->rotation == 360)
            {
                this->rotation = 0;
            }
            else this->rotation += 1; 
}
void Object::rotate_to_left()
{
    this->vector.x = cos( DEG2RAD * this->rotation);
    this->vector.y = sin( DEG2RAD * this->rotation);
    if (this->rotation == 360)
            {
                this->rotation = 0;
            }
            else this->rotation -= 1; 
}
float Object::getRotation()
{
    return this->rotation;
}
void Object::drift()
{
  
    this->position = Vector2Add(this->position, Vector2Scale(this->vector, this->speed));
    if(this->outofBounds())
    {
        if(this->outLeft())
            this->position.x = this->screenWidth - 1;
        if(this->outRight())
            this->position.x = 1;
        if(this->outDown())
            this->position.y = 1;
        if(this->outRight())
            this->position.y = this->screenHeight - 1;
    }
    DrawTexturePro(this->texture, this->hitbox, this->getDestRec(), this->getOrigin(), this->rotation, this->color);
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
bool Object::outofBounds()
{
    if(this->position.x < 0 || this->position.x > this->screenWidth || this->position.y < 0 || this->position.y > screenHeight )
        return true;
    else 
        return false;
}
bool Object::outLeft()
{
    if(this->position.x < 0)
        return true;
    else 
        return false;
}
bool Object::outRight()
{
    if(this->position.x > this->screenWidth)
        return true;
    else 
        return false;
}
bool Object::outDown()
{
    if(this->position.y > screenHeight)
        return true;
    else 
        return false;
}
bool Object::outUp()
{
    if(this->position.y < 0)
        return true;
    else 
        return false;
}
float Object::getSpeed()
{
    return this->speed;
}
void Object::setSpeed(float s)
{
    this->speed = s;
}
Ship::Ship(Texture2D texture, Color color, float scale, const int screenWidth, const int screenHeight, float speed, Texture2D beam_sprite) : Object(texture, color, scale, screenWidth, screenHeight, speed)
{
    this->deaths = 0;
    this->beam_sprite = beam_sprite;
    this->number_of_beams = 0;
    this->max_num_beams = 30;
}
void Ship::shoot()
{
    if(this->number_of_beams < this->max_num_beams)
        this->number_of_beams++;
    else
        this->number_of_beams = 1;
        this->beams[this->number_of_beams -1] = Object(this->beam_sprite, this->getColor(), 0.6 , this->getScreenWidth(), this->getScreenHeight(), 6.0);
        this->beams[this->number_of_beams -1].setPosition(Vector2Add(this->getPosition(), Vector2Scale(this->getVector(), 0.8 *this->getTexture().width)) );
        this->beams[this->number_of_beams -1].setVector(this->getVector());

}
void Ship::accelerate()
{   float speed_cap = 4.5f;
    float current_speed = this->getSpeed();
    if(current_speed < speed_cap)
        this->setSpeed(current_speed + 0.20);
    else 
        this->setSpeed(speed_cap);
}

void Ship::drift_beams()
{
    if(this->number_of_beams != 0)
    {
        for(int i = 0; i < this->number_of_beams; i++)
    {
        this->beams[i].drift();
    }
    }
    
}
int Ship::getNumBeams()
{
 return this->number_of_beams;
}



