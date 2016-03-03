#include "box.h"
using namespace boxNS;

//=============================================================================
// default constructor
//=============================================================================
Box::Box() : Entity()
{
    spriteData.width = WIDTH;           // size of character
    spriteData.height = HEIGHT;
    spriteData.x = X;                   // location on screen
    spriteData.y = Y;
    spriteData.rect.bottom = HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = WIDTH;
	oldX = boxNS::X;
	oldY = boxNS::Y;
    edge.top    = EDGE_TOP;             // ROTATED_BOX collision edges
    edge.bottom = EDGE_BOTTOM;
    edge.left   = EDGE_LEFT;
    edge.right  = EDGE_RIGHT;
	maxVelocity = 100;
    velocity.x = 0;
    velocity.y = 0;
    frameDelay = WALKING_ANIMATION_DELAY;
	startFrame = START_FRAME; //first frame of walk foreward animation
	endFrame = END_FRAME;	//last frame of walk foreward animation
    currentFrame = startFrame;
    radius = WIDTH/2.0;
    collisionType = entityNS::ROTATED_BOX;
	health = 10;	//health when box is instantiated
	mass = boxNS::MASS;
}

//=============================================================================
// Initialize the character.
// Post: returns true if successful, false if failed
//=============================================================================
bool Box::initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}


//=============================================================================
// Determines if the box's health is low
//=============================================================================
bool Box::isHealthLow()
{
	//if the health is below 25% returns true, if not then returns false
	if(health <= FULL_HEALTH/4)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//=============================================================================
// Determines if the box is dead
//=============================================================================
bool Box::isDead()
{
	//if the health is at or below 0 returns true, if not then returns false
	if(health <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//=============================================================================
// Calculates the remaining health of box after taking damage from player
//=============================================================================
void Box::takeDamage()
{
	health -= DAMAGE;
}


//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Box::update(float frameTime)
{
    Entity::update(frameTime);

    oldX = spriteData.x;                        // save current position
    oldY = spriteData.y;


	spriteData.x += frameTime * velocity.x;     // move box along X 
    spriteData.y += frameTime * velocity.y;     // move box along Y
}

//=============================================================================
// seek
//=============================================================================
void Box::seek(float targetX, float targetY)
{
	//declare vector variables
	VECTOR2 desiredVelocity;
	VECTOR2 steering;

	//calculate the desired velocity and normalize it
	float x = targetX - spriteData.x;
	float y = targetY - spriteData.y;
	normalize(x,y);
	desiredVelocity.x = x * maxVelocity;
	desiredVelocity.y = y * maxVelocity;

	//make the steering equal to the desired velocity minus the current velocity
	steering = desiredVelocity - velocity;

	//configure in the mass of the object
	steering = steering/mass;

	//make the current velocity equal to that of the velocity plus the steering calculations
	velocity = velocity + steering;

	//stop object from leaving edges of screen
	if (spriteData.y < 0)
	{
		spriteData.y = 0;
	}
	if (spriteData.y > GAME_HEIGHT - HEIGHT)
	{
		spriteData.y = GAME_HEIGHT - HEIGHT;
	}
	if (spriteData.x < 0)
	{
		spriteData.x = 0;
	}
	if (spriteData.x > GAME_WIDTH - WIDTH)
	{
		spriteData.x = GAME_WIDTH - WIDTH;
	}
}


//=============================================================================
// evade
//=============================================================================
void Box::flee(float targetX, float targetY)
{
	//declare vector variables
	VECTOR2 desiredVelocity;
	VECTOR2 steering;

	//calculate the desired velocity and normalize it
	float x = targetX - spriteData.x;
	float y = targetY - spriteData.y;
	normalize(x,y);
	desiredVelocity.x = -x * maxVelocity;
	desiredVelocity.y = -y * maxVelocity;

	//make the steering equal to the desired velocity minus the current velocity
	steering = desiredVelocity - velocity;

	//configure in the mass of the object
	steering = steering/mass;

	//make the current velocity equal to that of the velocity plus the steering calculations
	velocity = velocity + steering;

	//stop object from leaving edges of screen
	if (spriteData.y < 0)
	{
		spriteData.y = 0;
	}
	if (spriteData.y > GAME_HEIGHT - HEIGHT)
	{
		spriteData.y = GAME_HEIGHT - HEIGHT;
	}
	if (spriteData.x < 0)
	{
		spriteData.x = 0;
	}
	if (spriteData.x > GAME_WIDTH - WIDTH)
	{
		spriteData.x = GAME_WIDTH - WIDTH;
	}
}

//=============================================================================
// calculate magnitude of a vector
//=============================================================================
float Box::calculateMagnitude(float x, float y)
{
	//calculate the length (or magnitude) of the vector
	float magnitude;
	magnitude = sqrtf((x*x) + (y*y));
	return magnitude;
}

//=============================================================================
// normalize a vector
//=============================================================================
void Box::normalize(float &x, float &y)
{
	//calculate the length (or magnitude) of the vector
	float mag;
	mag = calculateMagnitude(x, y);

	//then divide each of its components by its length
	x = x/mag;
	y = y/mag;
}
