// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// flowerPower.cpp v1.0
// flowerPower is the class we create.

#include "flowerPower.h"
using namespace flowerPowerNS;

//=============================================================================
// Constructor
//=============================================================================
FlowerPower::FlowerPower()
{
    mapX = 0;
	score = 0;
    menuOn = true;
	instructionsOn = false;
	winScreenOn = false;
	loseScreenOn = false;
	box2.deactivate();
	box3.deactivate();
	box4.deactivate();
	box5.deactivate();
	evilBox2.deactivate();
	evilBox3.deactivate();
	evilBox4.deactivate();
	evilBox5.deactivate();
}

//=============================================================================
// Destructor
//=============================================================================
FlowerPower::~FlowerPower()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// initializes the game
//=============================================================================
void FlowerPower::initialize(HWND hwnd)
{
    Game::initialize(hwnd);

	//initialize DriectX fonts
	fontHealth.initialize(graphics, flowerPowerNS::FONT_HEALTH_SIZE, false, false, flowerPowerNS::FONT);

	//initialize DriectX fonts
	fontScore.initialize(graphics, flowerPowerNS::FONT_SCORE_SIZE, false, false, flowerPowerNS::FONT);

    // menu texture
    if (!menuTexture.initialize(graphics,MENU_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));

	    // winScreen texture
    if (!winScreenTexture.initialize(graphics,WINSCREEN_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing win screen texture"));

		    // loseScreen texture
    if (!loseScreenTexture.initialize(graphics,LOSESCREEN_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing lose screen texture"));

	  // instructions texture
    if (!instructionsTexture.initialize(graphics,INSTRUCTIONS_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing instructions texture"));

    // map background textures
    if (!tileBackgroundTextures.initialize(graphics,TILE_BACKGROUND_TEXTURES))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile background textures"));

	// map foreground textures
    if (!tileForegroundTextures.initialize(graphics,TILE_FOREGROUND_TEXTURES))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile background textures"));

    // object textures
    if (!objectTextures.initialize(graphics,OBJECT_TEXTURES))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing object textures"));

	// character textures
    if (!characterTextures.initialize(graphics,CHARACTER_TEXTURES))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing character textures"));

	// box textures
    if (!boxTextures.initialize(graphics,BOX_TEXTURES))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing box textures"));

	// box2 textures
    if (!boxTextures2.initialize(graphics,BOX_TEXTURES2))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing box2 textures"));

	// box3 textures
    if (!boxTextures3.initialize(graphics,BOX_TEXTURES3))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing box3 textures"));

	// box4 textures
    if (!boxTextures4.initialize(graphics,BOX_TEXTURES4))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing box4 textures"));

	// box5 textures
    if (!boxTextures5.initialize(graphics,BOX_TEXTURES5))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing box5 textures"));

	// evilBox textures
    if (!evilBoxTextures.initialize(graphics,EVILBOX_TEXTURES))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing box textures"));

		// evilBox textures2
    if (!evilBoxTextures2.initialize(graphics,EVILBOX_TEXTURES2))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing box textures"));

		// evilBox textures3
    if (!evilBoxTextures3.initialize(graphics,EVILBOX_TEXTURES3))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing box textures"));

		// evilBox textures4
    if (!evilBoxTextures4.initialize(graphics,EVILBOX_TEXTURES4))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing box textures"));

		// evilBox textures5
    if (!evilBoxTextures5.initialize(graphics,EVILBOX_TEXTURES5))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing box textures"));

	// main game textures
    if (!gameTextures.initialize(graphics,TEXTURES_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

    // menu image
    if (!menu.initialize(graphics,0,0,0,&menuTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));

	    // winScreen image
    if (!winScreen.initialize(graphics,0,0,0,&winScreenTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing winScreen"));

		    // loseScreen image
    if (!loseScreen.initialize(graphics,0,0,0,&loseScreenTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing loseScreen"));

	    // instructions image
    if (!instructions.initialize(graphics,0,0,0,&instructionsTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing instructions"));

    // tile background image
    if (!tileBackground.initialize(graphics,TEXTURE_SIZE,TEXTURE_SIZE,TEXTURE_COLS,&tileBackgroundTextures))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background tile"));
    tileBackground.setFrames(0, 0);
    tileBackground.setCurrentFrame(0);

	// tile foreground image
    if (!tileForeground.initialize(graphics,TEXTURE_SIZE,TEXTURE_SIZE,TEXTURE_FOREGROUND_COLS,&tileForegroundTextures))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing foreground tile"));
    tileForeground.setFrames(0, 0);
    tileForeground.setCurrentFrame(0);

	//character image
	if (!character.initialize(this,characterNS::WIDTH,characterNS::HEIGHT,characterNS::TEXTURE_COLS,&characterTextures))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing character"));
	character.setFrames(characterNS::STANDING_STILL, characterNS::STANDING_STILL);
    character.setCurrentFrame(characterNS::STANDING_STILL);
	//Start the character in the center
	character.setX(GAME_WIDTH/2 - characterNS::WIDTH);
    character.setY(GAME_HEIGHT/2 - characterNS::HEIGHT);

	//box image
	if (!box.initialize(this,boxNS::WIDTH,boxNS::HEIGHT,boxNS::TEXTURE_COLS,&boxTextures))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing box"));
	box.setFrames(boxNS::START_FRAME, boxNS::END_FRAME);
	box.setCurrentFrame(boxNS::START_FRAME);
	//Start the box away from the character
	box.setX(GAME_WIDTH/3 - characterNS::WIDTH);
    box.setY(GAME_HEIGHT/3 - characterNS::HEIGHT);

		//box2 image
	if (!box2.initialize(this,boxNS::WIDTH,boxNS::HEIGHT,boxNS::TEXTURE_COLS,&boxTextures2))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing box2"));
	box2.setFrames(boxNS::START_FRAME, boxNS::END_FRAME);
	box2.setCurrentFrame(boxNS::START_FRAME);
	//Start the box away from the character
	box2.setX(GAME_WIDTH/4 - characterNS::WIDTH);
    box2.setY(GAME_HEIGHT/4 - characterNS::HEIGHT);

		//box3 image
	if (!box3.initialize(this,boxNS::WIDTH,boxNS::HEIGHT,boxNS::TEXTURE_COLS,&boxTextures3))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing box3"));
	box3.setFrames(boxNS::START_FRAME, boxNS::END_FRAME);
	box3.setCurrentFrame(boxNS::START_FRAME);
	//Start the box away from the character
	box3.setX(GAME_WIDTH/6 - characterNS::WIDTH);
    box3.setY(GAME_HEIGHT/6 - characterNS::HEIGHT);

		//box4 image
	if (!box4.initialize(this,boxNS::WIDTH,boxNS::HEIGHT,boxNS::TEXTURE_COLS,&boxTextures4))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing box4"));
	box4.setFrames(boxNS::START_FRAME, boxNS::END_FRAME);
	box4.setCurrentFrame(boxNS::START_FRAME);
	//Start the box away from the character
	box4.setX(GAME_WIDTH/3 - characterNS::WIDTH);
    box4.setY(GAME_HEIGHT/3 - characterNS::HEIGHT);

		//box5 image
	if (!box5.initialize(this,boxNS::WIDTH,boxNS::HEIGHT,boxNS::TEXTURE_COLS,&boxTextures5))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing box"));
	box5.setFrames(boxNS::START_FRAME, boxNS::END_FRAME);
	box5.setCurrentFrame(boxNS::START_FRAME);
	//Start the box away from the character
	box5.setX(GAME_WIDTH/5 - characterNS::WIDTH);
    box5.setY(GAME_HEIGHT/5 - characterNS::HEIGHT);

	//evilBox image
	if (!evilBox.initialize(this,boxNS::WIDTH,boxNS::HEIGHT,boxNS::TEXTURE_COLS,&evilBoxTextures))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing evil box"));
	evilBox.setFrames(boxNS::START_FRAME, boxNS::END_FRAME);
	evilBox.setCurrentFrame(boxNS::START_FRAME);
	//Start the evil box away from the character
	evilBox.setX(GAME_WIDTH/4 - characterNS::WIDTH);
    evilBox.setY(GAME_HEIGHT/4 - characterNS::HEIGHT);

		//evilBox2 image
	if (!evilBox2.initialize(this,boxNS::WIDTH,boxNS::HEIGHT,boxNS::TEXTURE_COLS,&evilBoxTextures2))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing evil box2"));
	evilBox2.setFrames(boxNS::START_FRAME, boxNS::END_FRAME);
	evilBox2.setCurrentFrame(boxNS::START_FRAME);
	//Start the evil box away from the character
	evilBox2.setX(GAME_WIDTH/2 - characterNS::WIDTH);
    evilBox2.setY(GAME_HEIGHT/2 - characterNS::HEIGHT);

		//evilBox3 image
	if (!evilBox3.initialize(this,boxNS::WIDTH,boxNS::HEIGHT,boxNS::TEXTURE_COLS,&evilBoxTextures3))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing evil box3"));
	evilBox3.setFrames(boxNS::START_FRAME, boxNS::END_FRAME);
	evilBox3.setCurrentFrame(boxNS::START_FRAME);
	//Start the evil box away from the character
	evilBox3.setX(GAME_WIDTH/4 - characterNS::WIDTH);
    evilBox3.setY(GAME_HEIGHT/4 - characterNS::HEIGHT);

		//evilBox4 image
	if (!evilBox4.initialize(this,boxNS::WIDTH,boxNS::HEIGHT,boxNS::TEXTURE_COLS,&evilBoxTextures4))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing evil box4"));
	evilBox4.setFrames(boxNS::START_FRAME, boxNS::END_FRAME);
	evilBox4.setCurrentFrame(boxNS::START_FRAME);
	//Start the evil box away from the character
	evilBox4.setX(GAME_WIDTH/3 - characterNS::WIDTH);
    evilBox4.setY(GAME_HEIGHT/4 - characterNS::HEIGHT);

		//evilBox5 image
	if (!evilBox5.initialize(this,boxNS::WIDTH,boxNS::HEIGHT,boxNS::TEXTURE_COLS,&evilBoxTextures5))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing evil box5"));
	evilBox5.setFrames(boxNS::START_FRAME, boxNS::END_FRAME);
	evilBox5.setCurrentFrame(boxNS::START_FRAME);
	//Start the evil box away from the character
	evilBox5.setX(GAME_WIDTH/5 - characterNS::WIDTH);
    evilBox5.setY(GAME_HEIGHT/4 - characterNS::HEIGHT);

	// health bar
	healthBar.initialize(graphics, &gameTextures, flowerPowerNS::CHARACTER_HEALTHBAR_X, flowerPowerNS::CHARACTER_HEALTHBAR_Y, 10.0f, graphicsNS::WHITE);

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void FlowerPower::update()
{
    float characterX;

    if (menuOn)
    {
		if (input->anyKeyPressed())
        {
            menuOn = false;
            input->clearAll();
			instructionsOn = true;
        }
    }
	else if(instructionsOn)
	{
		if (input->anyKeyPressed())
		{
			instructionsOn = false;
			input->clearAll();
		}
	}
	else
	{

		if(score >= 5)
		{
			winScreenOn = true;
		}
		
		character.update(frameTime);        // update the character

		//check to see which key is presses down so corrisponding animation plays
		if (input->isKeyDown(UP_KEY))       // if up
		{
			character.setFrames(characterNS::FOREWARD_START_FRAME, characterNS::FOREWARD_END_FRAME);
		}
		else if (input->isKeyDown(DOWN_KEY))     // if down
		{
			character.setFrames(characterNS::BACKWARD_START_FRAME, characterNS::BACKWARD_END_FRAME);
		}
		else if (input->isKeyDown(LEFT_KEY))     // if left
		{
			character.setFrames(characterNS::LEFT_START_FRAME, characterNS::LEFT_END_FRAME);
		}
		else if (input->isKeyDown(RIGHT_KEY))    // if right
		{
			character.setFrames(characterNS::LEFT_START_FRAME, characterNS::LEFT_END_FRAME);
		}
		else
		{
			character.setCurrentFrame(characterNS::STANDING_STILL);
		}//end character animations


		//check to see if character is dead
		if(character.getHealth() <= 0)
		{
			loseScreenOn = true;
		}


		//check to see if the box is dead
		if(box.isDead() == true && box.getActive() == true)
		{
			box.deactivate();
			box2.activate();
			score++;
		}
		else
		{
			//make the box evade the character
			box.flee(character.getX(), character.getY());
			box.update(frameTime);
		}

			//check to see if the box is dead
		if(box2.isDead() == true && box2.getActive() == true)
		{
			box2.deactivate();
			box3.activate();
			score++;
		}
		else if(box2.getActive() == true)
		{
			//make the box evade the character
			box2.flee(character.getX(), character.getY());
			box2.update(frameTime);
		}

			//check to see if the box is dead
		if(box3.isDead() == true && box3.getActive() == true)
		{
			box3.deactivate();
			box4.activate();
			score++;
		}
		else if(box3.getActive() == true)
		{
			//make the box evade the character
			box3.flee(character.getX(), character.getY());
			box3.update(frameTime);
		}

			//check to see if the box is dead
		if(box4.isDead() == true && box4.getActive() == true)
		{
			box4.deactivate();
			box5.activate();
			score++;
		}
		else if(box4.getActive() == true)
		{
			//make the box evade the character
			box4.flee(character.getX(), character.getY());
			box4.update(frameTime);
		}

			//check to see if the box is dead
		if(box5.isDead() == true && box5.getActive() == true)
		{
			box5.deactivate();
			score++;
		}
		else if(box5.getActive() == true)
		{
			//make the box evade the character
			box5.flee(character.getX(), character.getY());
			box5.update(frameTime);
		}

		//check to see if the evil box is dead
		if(evilBox.isDead() == true && evilBox.getActive() == true)
		{
			evilBox.deactivate();
			evilBox2.activate();
			character.takeDamage();
		}
		else if(evilBox.getActive() == true)
		{
			//make the evil box seek out the character
			evilBox.seek(character.getX(), character.getY());
			evilBox.update(frameTime);
		}

				//check to see if the evil box is dead
		if(evilBox2.isDead() == true && evilBox2.getActive() == true)
		{
			evilBox2.deactivate();
			evilBox3.activate();
			character.takeDamage();
		}
		else if(evilBox2.getActive() == true)
		{
			//make the evil box seek out the character
			evilBox2.seek(character.getX(), character.getY());
			evilBox2.update(frameTime);
		}

				//check to see if the evil box is dead
		if(evilBox3.isDead() == true && evilBox3.getActive() == true)
		{
			evilBox3.deactivate();
			evilBox4.activate();
			character.takeDamage();
		}
		else if(evilBox3.getActive() == true)
		{
			//make the evil box seek out the character
			evilBox3.seek(character.getX(), character.getY());
			evilBox3.update(frameTime);
		}

				//check to see if the evil box is dead
		if(evilBox4.isDead() == true && evilBox4.getActive() == true)
		{
			evilBox4.deactivate();
			evilBox5.activate();
			character.takeDamage();
		}
		else if(evilBox4.getActive() == true)
		{
			//make the evil box seek out the character
			evilBox4.seek(character.getX(), character.getY());
			evilBox.update(frameTime);
		}

				//check to see if the evil box is dead
		if(evilBox5.isDead() == true && evilBox5.getActive() == true)
		{
			evilBox5.deactivate();
			character.takeDamage();
		}
		else if(evilBox5.getActive() == true)
		{
			//make the evil box seek out the character
			evilBox5.seek(character.getX(), character.getY());
			evilBox5.update(frameTime);
		}

		characterX = character.getX();
		if(characterX < 0)                  // if character off screen left
		{
			mapX -= characterNS::SPEED * frameTime;  // scroll map right
			character.setX(0);              // put character at left edge
		}
		// if character off screen right
		else if(characterX > GAME_WIDTH - character.getWidth())
		{
			mapX -= characterNS::SPEED * frameTime;  // scroll map left
			// put character at right edge
			character.setX((float)(GAME_WIDTH - character.getWidth()));
		}

		if(mapX > 0)    // if map past left edge
		{
			mapX = 0;   // stop at left edge of map
			character.setVelocityX(0);  // stop character
		}
		// if map past right edge
		else if(mapX < (-MAP_WIDTH * TEXTURE_SIZE) + GAME_WIDTH)
		{
			// stop at right edge of map
			mapX = (-MAP_WIDTH * TEXTURE_SIZE) + GAME_WIDTH;
			character.setVelocityX(0);  // stop character
		}
	}
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void FlowerPower::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void FlowerPower::collisions()
{
	VECTOR2 collisionVector;

	//if collision between character and box
	if(character.collidesWith(box, collisionVector))
	{
		box.takeDamage();
	}

		//if collision between character and box2
	if(character.collidesWith(box2, collisionVector))
	{
		box2.takeDamage();
	}

		//if collision between character and box3
	if(character.collidesWith(box3, collisionVector))
	{
		box3.takeDamage();
	}

		//if collision between character and box4
	if(character.collidesWith(box4, collisionVector))
	{
		box4.takeDamage();
	}

		//if collision between character and box5
	if(character.collidesWith(box5, collisionVector))
	{
		box5.takeDamage();
	}

	//if collision between character and evil box
	if(character.collidesWith(evilBox, collisionVector))
	{
		evilBox.takeDamage();
	}

		//if collision between character and evil box2
	if(character.collidesWith(evilBox2, collisionVector))
	{
		evilBox2.takeDamage();
	}

		//if collision between character and evil box3
	if(character.collidesWith(evilBox3, collisionVector))
	{
		evilBox3.takeDamage();
	}

		//if collision between character and evil box4
	if(character.collidesWith(evilBox4, collisionVector))
	{
		evilBox4.takeDamage();
	}

		//if collision between character and evil box5
	if(character.collidesWith(evilBox5, collisionVector))
	{
		evilBox5.takeDamage();
	}
}

//=============================================================================
// Reset variables
// Start at main menu
//=============================================================================
void FlowerPower::resetGame()
{
	menuOn = true;
	winScreenOn = false;
	loseScreenOn = false;
	instructionsOn = false;
	score = 0;
	character.setHealth(100.0);
	character.setFrames(characterNS::STANDING_STILL, characterNS::STANDING_STILL);
	character.setCurrentFrame(characterNS::STANDING_STILL);
	//Start the character in the center
	character.setX(GAME_WIDTH/2 - characterNS::WIDTH);
	character.setY(GAME_HEIGHT/2 - characterNS::HEIGHT);
	box.activate();
	box2.deactivate();
	box3.deactivate();
	box4.deactivate();
	box5.deactivate();
	evilBox.activate();
	evilBox2.deactivate();
	evilBox3.deactivate();
	evilBox4.deactivate();
	evilBox5.deactivate();
}


//=============================================================================
// Render game items
//=============================================================================
void FlowerPower::render()
{
    graphics->spriteBegin();

	for(int row=0; row<MAP_HEIGHT; row++)       // for each row of map
	{
		tileBackground.setY( (float)(row*TEXTURE_SIZE) ); // set tile Y
		for(int col=0; col<MAP_WIDTH; col++)    // for each column of map
		{
			if(tileMapBackground[row][col] > 0)          // if tile present
			{
				tileBackground.setCurrentFrame(tileMapBackground[row][col] - 1);    // set tile texture - have to subtract 1 bc gid in Tiled starts at index 1 instead of 0
				tileBackground.setX( (float)(col*TEXTURE_SIZE) + mapX );   // set tile X
				// if tile on screen
				if(tileBackground.getX() > -TEXTURE_SIZE && tileBackground.getX() < GAME_WIDTH)
					tileBackground.draw();                // draw tile
			}
		}
	}

	//draw character
	character.draw();

	for(int row=0; row<MAP_HEIGHT; row++)       // for each row of map
	{
		tileForeground.setY( (float)(row*TEXTURE_SIZE) ); // set tile Y
		for(int col=0; col<MAP_WIDTH; col++)    // for each column of map
		{
			if(tileMapForeground[row][col] > 0)          // if tile present
			{
				tileForeground.setCurrentFrame(tileMapForeground[row][col] - 73);    // set tile texture - have to subtract 1 + gid count from previous texture
				tileForeground.setX( (float)(col*TEXTURE_SIZE) + mapX );   // set tile X
				// if tile on screen
				if(tileForeground.getX() > -TEXTURE_SIZE && tileForeground.getX() < GAME_WIDTH)
					tileForeground.draw();                // draw tile
			}
		}
	}

	//draw box if it is not dead
	if(box.getActive() == true)
	{
		box.draw();
	}

		//draw box2 if it is not dead
	if(box2.getActive() == true)
	{
		box2.draw();
	}

		//draw box3 if it is not dead
	if(box3.getActive() == true)
	{
		box3.draw();
	}

		//draw box4 if it is not dead
	if(box4.getActive() == true)
	{
		box4.draw();
	}

		//draw box if it is not dead
	if(box5.getActive() == true)
	{
		box5.draw();
	}

	//draw evilBox if it is not dead
	if(evilBox.getActive() == true)
	{
		evilBox.draw();
	}

		//draw evilBox2 if it is not dead
	if(evilBox2.getActive() == true)
	{
		evilBox2.draw();
	}

		//draw evilBox3 if it is not dead
	if(evilBox3.getActive() == true)
	{
		evilBox3.draw();
	}

		//draw evilBox4 if it is not dead
	if(evilBox4.getActive() == true)
	{
		evilBox4.draw();
	}

		//draw evilBox5 if it is not dead
	if(evilBox5.getActive() == true)
	{
		evilBox5.draw();
	}

	// display health bar
    healthBar.setX((float)flowerPowerNS::CHARACTER_HEALTHBAR_X);
    healthBar.set(character.getHealth());
    healthBar.draw(flowerPowerNS::CHARACTER_COLOR);

	//display health text
	fontHealth.setFontColor(flowerPowerNS::FONT_COLOR);
	_snprintf_s(buffer, flowerPowerNS::BUF_SIZE, "%d", (int)character.getHealth());
	fontHealth.print(buffer,flowerPowerNS::CHARACTER_HEALTHBAR_X,flowerPowerNS::CHARACTER_HEALTHBAR_Y + 100);

	//display score text
	fontScore.setFontColor(flowerPowerNS::FONT_COLOR);
	_snprintf_s(buffer, flowerPowerNS::BUF_SIZE, "%d", (int)score);
	fontScore.print(buffer,flowerPowerNS::CHARACTER_SCORE_X,flowerPowerNS::CHARACTER_SCORE_Y);

    if(menuOn)
        menu.draw();

	if(winScreenOn)
		winScreen.draw();

	if(loseScreenOn)
		loseScreen.draw();

	if(instructionsOn)
		instructions.draw();

    graphics->spriteEnd();
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void FlowerPower::releaseAll()
{
    menuTexture.onLostDevice();
	winScreenTexture.onLostDevice();
	loseScreenTexture.onLostDevice();
    tileBackgroundTextures.onLostDevice();
	tileForegroundTextures.onLostDevice();
	characterTextures.onLostDevice();
    objectTextures.onLostDevice();
	boxTextures.onLostDevice();
	evilBoxTextures.onLostDevice();
	gameTextures.onLostDevice();
	fontHealth.onLostDevice();
	fontScore.onLostDevice();

    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void FlowerPower::resetAll()
{
    tileBackgroundTextures.onResetDevice();
	tileForegroundTextures.onResetDevice();
    objectTextures.onResetDevice();
	boxTextures.onResetDevice();
	evilBoxTextures.onResetDevice();
	characterTextures.onResetDevice();
    menuTexture.onResetDevice();
	winScreenTexture.onResetDevice();
	loseScreenTexture.onResetDevice();
	gameTextures.onResetDevice();
	fontHealth.onResetDevice();
	fontScore.onResetDevice();

    Game::resetAll();
    return;
}
