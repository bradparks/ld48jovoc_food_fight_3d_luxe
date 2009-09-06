#ifndef BENEATH_GAME_H
#define BENEATH_GAME_H

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <windows.h>
#include <crtdbg.h>
#endif

#include <iostream>
#include <fstream>
#include <string>

#include <time.h>

#include <SDL.h>
#include <SDL_endian.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include <il/il.h>
#include <il/ilu.h>
#include <il/ilut.h>

#include <enet/enet.h>

#include <Shape.h>
#include <Cavern.h>
#include <Editor.h>
#include <GameObj.h>
#include <PlayerShip.h>

// protobufs for packets
#include <pbSpaceCave/SpaceCave.pb.h>

// no point in having more since only 8 players max
#define MAX_CLIENTS (8)

// just some port above 49152
#define SPACECAVE_PORT (62511)

// Channels
enum {
	NET_CHANNEL_CHAT,	
	NET_CHANNEL_GAMEUPDATE,

	NUM_NET_CHANNELS
};

// ==================================================
enum {
	PacketType_CHAT_MESSAGE = 100,	

	PacketType_LAST
};

// ==================================================
class Server
{
public:
	Server( std::vector<Shape*> &shapes, bool singlePlayer );
	~Server();
	
	// during game state itself	
	void game_updateSim( float dt );	
	void game_update( float dt );

	void net_update( );	

	// Game play happenings
	PlayerShip *addPlayer();
	
	//void game_keypress( SDL_KeyboardEvent &key );	
	void init();
	void initNetwork( );

	void newGame();

	// some shortcuts in single player mode
	bool m_singlePlayer;

	std::vector<PlayerShip*> m_ships;

	Cavern *m_level;	

protected:

	// Networking stuff
	ENetAddress m_serverAddr;
	ENetHost *m_clientHost;
	std::vector<ENetPeer*> m_clientPeers;

	void sendPacketEveryone( int channel, pbSpaceCave::Packet &pbPacket );
	void sendPacketPeer( int channel, pbSpaceCave::Packet &pbPacket, ENetPeer *peer  );

	void newConnection( ENetPeer *peer );
	
	void doIdentity( pbSpaceCave::Packet &pbPacket, ENetPeer *peer );

	void handlePacket( int channel, ENetPacket *packet, ENetPeer *peer );

	// Game stuff
	bool m_isInit;	
	std::vector<Shape*> &m_shapes;	
};

#endif