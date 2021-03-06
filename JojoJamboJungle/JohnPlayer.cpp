#pragma once
#include "JohnPlayer.h"
#include "utils.h"
#include "Player.h"

JohnPlayer::JohnPlayer()
{
	this->position.x = 0;
	this->position.y = 0;
}

JohnPlayer::JohnPlayer(Position & position)
{
	this->position.x = position.x;
	this->position.y = position.y;
}

JohnPlayer::~JohnPlayer()
{
}

const int JohnPlayer::getPositionX()
{
	return this->position.x;
}

const int JohnPlayer::getPositionY()
{
	return this->position.y;
}

void JohnPlayer::setPositionX(const int & xPosition)
{
	this->position.x = xPosition;
}

void JohnPlayer::setPositionY(const int & yPosition)
{
	this->position.y = yPosition;
}

const int JohnPlayer::getWidth() const
{
	// TODO: insert return statement here
	return 0;
}

const int JohnPlayer::getHeight() const
{
	// TODO: insert return statement here
	return 0;
}
