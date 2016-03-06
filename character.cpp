#include "character.h"
using namespace characterNS;

//=============================================================================
// default constructor
//=============================================================================
Character::Character() : Entity()
{
    spriteData.width = WIDTH;           // size of character
    spriteData.height = HEIGHT;
    spriteData.x = X;                   // location on screen
    spriteData.y = Y;
    spriteData.rect.bottom = HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = WIDTH;
    edge.top    = EDGE_TOP;             // ROTATED_BOX collision edges
    edge.bottom = EDGE_BOTTOM;
    edge.left   = EDGE_LEFT;
    edge.right  = EDGE_RIGHT;
    velocity.x = 0;
    velocity.y = 0;
    frameDelay = WALKING_ANIMATION_DELAY;
	forewardStart = FOREWARD_START_FRAME; //first frame of walk foreward animation
	forewardEnd = FOREWARD_END_FRAME;	//last frame of walk foreward animation
	backwardStart = BACKWARD_START_FRAME; //first frame of walk backward animation
	backwardEnd = BACKWARD_END_FRAME;	//last frame of walk backward animation
	leftStart = LEFT_START_FRAME; //first frame of walk left animation
	leftEnd = LEFT_END_FRAME;	//last frame of walk left animation
	stillFrame = STANDING_STILL; //still frame
    currentFrame = startFrame;
    radius = WIDTH/2.0;
    collisionType = entityNS::ROTATED_BOX;
	health = FULL_HEALTH; //set health to full when character is instantiated
}

//=============================================================================
// Initialize the character.
// Post: returns true if successful, false if failed
//=============================================================================
bool Character::initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}


//=============================================================================
// Calculates the remaining health of player after attacked by an enemy
//=============================================================================
void Character::takeDamage()
{
	health -= DAMAGE;
}


//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Character::update(float frameTime)
{
    Entity::update(frameTime);
	
	if (input->isKeyDown(UP_KEY))       // if up
    {
		spriteData.y = spriteData.y - frameTime * SPEED;
        if (spriteData.y < 0)
            spriteData.y = 0;
    }
    if (input->isKeyDown(DOWN_KEY))     // if down
    {
		spriteData.y = spriteData.y + frameTime * SPEED;
        if (spriteData.y > GAME_HEIGHT - HEIGHT)
            spriteData.y = GAME_HEIGHT - HEIGHT;
    }
    if (input->isKeyDown(LEFT_KEY))     // if left
    {
        this->flipHorizontal(false);
        spriteData.x -= frameTime * SPEED;
    }
    if (input->isKeyDown(RIGHT_KEY))    // if right
    {
        this->flipHorizontal(true);
        spriteData.x += frameTime * SPEED;
    }
	
}