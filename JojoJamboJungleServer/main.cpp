#include <SDL_net.h>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <thread>

#include "Player.h"

#define CLIENTS 1

std::vector<std::string> playersReceivedData;

struct UDPConnection
{
	UDPConnection()
	{
		quit = false;
	}
	~UDPConnection()
	{
		SDLNet_FreePacket(packet);
		SDLNet_Quit();
	}
	bool Init(const std::string &ip, int32_t remotePort, int32_t localPort)
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
	bool InitSDL_Net()
	{

		if (SDLNet_Init() == -1)
		{
			return false;
		}
		return true;
	}
	bool CreatePacket(int32_t packetSize)
	{
		packet = SDLNet_AllocPacket(packetSize);

		if (packet == nullptr)
		{
			return false;
		}
		packet->address.host = serverIP.host;
		packet->address.port = serverIP.port;
		return true;
	}
	bool OpenPort(int32_t port)
	{
		ourSocket = SDLNet_UDP_Open(port);

		if (ourSocket == nullptr)
		{
			return false;
		}
		return true;
	}
	bool SetIPAndPort(const std::string &ip, uint16_t port)
	{
		// Set IP and port number with correct endianess
		if (SDLNet_ResolveHost(&serverIP, ip.c_str(), port) == -1)
		{
			return false;
		}
		return true;
	}
	// Send data. 
	bool Send(const std::string &str)
	{
		return true;
	}
	void CheckForData()
	{
		
		if (SDLNet_UDP_Recv(ourSocket, packet))
		{
			std::cout << "Data received : " << packet->data << "\n";
			std::string data(packet->data, packet->data + packet->len);
			playersReceivedData.push_back(data);
		}
	}
	bool WasQuit()
	{
		return quit;
	}
private:
	bool quit;
	UDPsocket ourSocket;
	IPaddress serverIP;
	UDPpacket *packet;
};

void setPlayersIpAndPort(std::vector<Player>& players) {
	
	std::string ipNumber, localPortNumber, remotePortNumber;
	int playersNumber;
	std::cout << "\tNumber of players: ";
	std::cin >> playersNumber;

	for (size_t i = 0; i < playersNumber ; i++)
	{
		std::cout << "Player " + std::to_string(i) + " ip \n" << std::endl;
		std::cin >> ipNumber;
		std::cout << "Player " + std::to_string(i) + " local port number \n" << std::endl;
		std::cin >> localPortNumber;
		std::cout << "Player " + std::to_string(i) + " remote port number \n" << std::endl;
		std::cin >> localPortNumber;

		Player p(ipNumber, localPortNumber, remotePortNumber);
		players.push_back(p);
	}
}

void initPlayersUDPConnection(std::vector<Player> & players, std::vector<UDPConnection>& playersUDPConnection) {
	for (size_t i = 0; i < players.size(); i++)
	{
		std::string ip = players[i].ipAdress;
		int32_t localPort = std::stoi(players[i].localPortNumber);
		int32_t remotePort = std::stoi(players[i].remotePortNumber);

		UDPConnection connection;
		connection.Init(ip, localPort, remotePort);
		playersUDPConnection.push_back(connection);
	}
}

void createUDPDataThreads(std::vector<std::thread>& threads, std::vector<UDPConnection>& playersUDPConnection) {
	for (size_t i = 0; i < playersUDPConnection.size(); i++)
	{
		std::thread thread(&waitForData);
		threads.push_back(thread);
	}
}

void waitForData(UDPConnection connection) {
	while (!connection.WasQuit())
	{
		connection.CheckForData();
	}
}

int main(int argc, char **argv)
{

	std::vector<Player> players;
	std::vector<UDPConnection> playersUDPConnection;
	std::vector<std::thread> threads;

	return 0;

}