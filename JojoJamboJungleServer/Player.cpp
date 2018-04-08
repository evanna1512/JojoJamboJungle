#include "Player.h"

Player::Player(std::string ipAdress, std::string localPortNumber, std::string remotePortNumber)
{
	this->ipAdress = ipAdress;
	this->localPortNumber = localPortNumber;
	this->remotePortNumber = remotePortNumber;
}
