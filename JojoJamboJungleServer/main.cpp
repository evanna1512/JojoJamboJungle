#include <SDL_net.h>
#include <iostream>
#include <sstream>

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

UDPConnection udpConnection;

int main(int argc, char **argv)
{
	std::string IP;
	int32_t localPort = 0;
	int32_t remotePort = 0;

	udpConnection.Init("127.0.0.1", 123123, 321321);


	uint8_t command = 0;

	while (!udpConnection.WasQuit())
	{
		udpConnection.CheckForData();
	}

	return 0;
}