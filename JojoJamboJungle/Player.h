#pragma once
#include "utils.h"

struct PlayerState {
	/// should be in game state
	bool dead = false;
	int lives = 3;
	int score = 0;
	int level = 0;

};


class Player {
protected:
	Position position;
	PlayerState playerState;

public:
	// Constructor and destructor
	Player() {};
	virtual ~Player() {};

	// Positions of a player
	virtual const int getPositionX() const = 0;
	virtual const int getPositionY() const = 0;
	virtual void setPositionX(const int&) = 0;
	virtual void setPositionY(const int&) = 0;
	
	// Dimensions of a player
	virtual const int getWidth() const = 0;
	virtual const int getHeight()	const = 0;
};