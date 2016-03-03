#ifndef _BOX_H            // Prevent multiple definitions if this 
#define _BOX_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include <cmath>

namespace boxNS
{
    const int   WIDTH = 72;                // image width (each frame)
    const int   HEIGHT = 60;               // image height
    const int   X = GAME_WIDTH/2 - WIDTH/2; // location on screen
    const int   Y = GAME_HEIGHT/6 - HEIGHT;
    const int   EDGE_TOP = -60;             // For BOX and ROTATE_BOX collison.
    const int   EDGE_BOTTOM = 60;           // "   relative to center
    const int   EDGE_LEFT = -60;            // "
    const int   EDGE_RIGHT = 60;            // "
    const float SPEED = 96;                 // pixels per second
    enum DIRECTION {LEFT, RIGHT};           // direction
    const int   TEXTURE_COLS = 1;			// texture has 1 columns
	const int	START_FRAME = 0;		//	animation starting frame
	const int	END_FRAME = 0;			//animation ending frame
	const float WALKING_ANIMATION_DELAY = 0.15f;	//time between frames
	const float DAMAGE = 10; //amount of damage box takes from being hit by player
	const int MAX_STEPS = 300; //number of steps the box will take before turning around
	const float MAX_DISTANCE = 160; //maximum length in pixels that the character can be from the box and still trigger the isClose function
	const float ATTACK_RANGE = 32; //maximum length in pixels that the character can be from the box and still trigger attack function
	 const float MASS = 300.0f;              // mass
}

// inherits from Entity class
class Box : public Entity
{
private:
	 float   oldX, oldY;

public:
    // constructor
    Box();

    // inherited member functions
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM);
    void update(float frameTime);
    void repair();

    // new functions
    void setVelocityX(float v)  {velocity.x = v;}
	bool isHealthLow(); //determines if box's health is low
	void takeDamage(); //takes damage when attacked by player
	bool isDead(); //checks to see if the box is dead
    void seek(float targetX, float targetY); // enemy seeks out ship
	float calculateMagnitude(float x, float y); //calculate magnitude of vector
	void normalize(float &x, float &y); //normalize vector
	void flee(float targetX, float targetY);
};
#endif