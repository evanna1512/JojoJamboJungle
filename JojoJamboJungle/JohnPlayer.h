#pragma once
#include "Player.h"

class JohnPlayer : protected Player{
protected:
	Position position;
	PlayerState playerState;

public:
	JohnPlayer();
	JohnPlayer(int x, int y);
	JohnPlayer(Position&);
	~JohnPlayer();

	// Positions of a player
	int getPositionX();
	int getPositionY();
	void setPositionX(const int&);
	void setPositionY(const int&);

	// Dimensions of a player
	const int getWidth() const;
	const int getHeight() const;


};