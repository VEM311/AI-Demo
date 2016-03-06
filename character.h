#ifndef _CHARACTER_H            // Prevent multiple definitions if this 
#define _CHARACTER_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace characterNS
{
    const int   WIDTH = 64;                // image width (each frame)
    const int   HEIGHT = 96;               // image height
    const int   X = GAME_WIDTH/2 - WIDTH/2; // location on screen
    const int   Y = GAME_HEIGHT/6 - HEIGHT;
    const int   EDGE_TOP = -60;             // For BOX and ROTATE_BOX collison.
    const int   EDGE_BOTTOM = 60;           // "   relative to center
    const int   EDGE_LEFT = -60;            // "
    const int   EDGE_RIGHT = 60;            // "
    const float SPEED = 256;                 // pixels per second
    enum DIRECTION {LEFT, RIGHT};           // direction
    const int   TEXTURE_COLS = 3;			// texture has 3 columns
	const int FOREWARD_START_FRAME = 3;		//	animation starting frame
	const int FOREWARD_END_FRAME = 5;			//animation ending frame
	const int BACKWARD_START_FRAME = 0;		//	animation starting frame
	const int BACKWARD_END_FRAME = 2;			//animation ending frame
	const int STANDING_STILL = 1;		//still frame
	const int LEFT_START_FRAME = 6;		//	animation starting frame
	const int LEFT_END_FRAME = 8;			//animation ending frame
	const float WALKING_ANIMATION_DELAY = 0.15f;	//time between frames
	const float ATTACK_RANGE = 32; //maximum length in pixels that the character can be from the cat and still trigger attack function
	const int DAMAGE = 20; //damage taken when attacked by enemy

}

// inherits from Entity class
class Character : public Entity
{

public:
    // constructor
    Character();

    // inherited member functions
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM);
    void update(float frameTime);
    void repair();

    // new functions
    void setVelocityX(float v)  {velocity.x = v;}
	void takeDamage(); //takes damage when attacked by an enemy
};
#endif
