#include <iostream>
#include <sstream>
#include "Connection.h"


UDPConnection::UDPConnection()
{
	quit = false;
}

UDPConnection::~UDPConnection()
{
	SDLNet_FreePacket(packet);
	SDLNet_Quit();
}

bool UDPConnection::Init(const std::string &ip, int32_t remotePort, int32_t localPort)
{
	// Initialize SDL_net
	if (!InitSDL_Net())
		return false;

	if (!OpenPort(localPort))
		return false;

	if (!SetIPAndPort(ip, remotePort))
		return false;

	if (!CreatePacket(512))
		return false;

	return true;
}

bool UDPConnection::InitSDL_Net()
{
	if (SDLNet_Init() == -1)
	{
		std::cout << "SDLNet_Init failed : " << SDLNet_GetError() << std::endl;
		return false;
	}

	return true;
}

bool UDPConnection::CreatePacket(int32_t packetSize)
{
	packet = SDLNet_AllocPacket(packetSize);

	if (packet == nullptr)
	{
		std::cout << "SDLNet_AllocPacket failed : " << SDLNet_GetError() << std::endl;
		return false;
	}

	packet->address.host = serverIP.host;
	packet->address.port = serverIP.port;
	return true;
}

bool UDPConnection::OpenPort(int32_t port)
{
	ourSocket = SDLNet_UDP_Open(port);

	if (ourSocket == nullptr)
	{
		std::cout << "SDLNet_UDP_Open failed : " << SDLNet_GetError() << std::endl;
		return false;
	}

	std::cout << "Success!\n\n";
	return true;
}

bool UDPConnection::SetIPAndPort(const std::string &ip, uint16_t port)
{
	if (SDLNet_ResolveHost(&serverIP, ip.c_str(), port) == -1)
	{
		std::cout << "SDLNet_ResolveHost failed : " << SDLNet_GetError() << std::endl;
		return false;
	}

	return true;
}

bool UDPConnection::Send(const std::string &str)
{

	memcpy(packet->data, str.c_str(), str.length());
	packet->len = str.length();

	if (SDLNet_UDP_Send(ourSocket, -1, packet) == 0)
	{
		return false;
	}

	return true;
}

void UDPConnection::CheckForData()
{
	
	if (SDLNet_UDP_Recv(ourSocket, packet))
	{
		std::cout << "Data received : " << packet->data << "\n";
	}
}

bool UDPConnection::WasQuit()
{
	return quit;
}


