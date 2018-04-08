#pragma once
#include <string>

class Player {
public:
	std::string ipAdress;
	std::string localPortNumber;
	std::string remotePortNumber;
	int x;
	int y;
	bool isJumping;
	Player(std::string ipAdress, std::string localPortNumber, std::string remotePortNumber);
};