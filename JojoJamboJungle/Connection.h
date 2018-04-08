#include <SDL_net.h>
#include <iostream>
#include <sstream>

class UDPConnection {
private:
	bool quit;
	UDPsocket ourSocket;
	IPaddress serverIP;
	UDPpacket *packet;
	bool InitSDL_Net();
	bool CreatePacket(int32_t packetSize);
	bool OpenPort(int32_t port);
	bool SetIPAndPort(const std::string &ip, uint16_t port);


public:
	UDPConnection();
	~UDPConnection();
	bool Init(const std::string &ip, int32_t remotePort, int32_t localPort);
	bool Send(const std::string &str);
	void CheckForData();
	bool WasQuit();
};