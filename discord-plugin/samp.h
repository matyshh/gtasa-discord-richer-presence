#pragma once
#include <string>
#include <cstdint>
#define WIN32_LEAN_AND_MEAN
#include "query.h"
#include <windows.h>
#pragma pack(push, 1)

struct stSAMPPools {
	struct stActorPool* pActor;
	struct stObjectPool* pObject;
	struct stGangzonePool* pGangzone;
	struct stTextLabelPool* pText3D;
	struct stTextdrawPool* pTextdraw;
	void* pPlayerLabels;
	struct stPlayerPool* pPlayer;
	struct stVehiclePool* pVehicle;
	struct stPickupPool* pPickup;
};

struct stSAMP {
	void* pUnk0;
	struct stServerInfo* 		pServerInfo;
	uint8_t						byteSpace[24];
	char						szIP[257];
	char						szHostname[259];
	bool						bNametagStatus;
	uint32_t					ulPort;
	uint32_t					ulMapIcons[100];
	int							iLanMode;
	int							iGameState;
	uint32_t					ulConnectTick;
	struct stServerPresets* 	pSettings;
	void* 						pRakClientInterface;
	struct stSAMPPools* 		pPools;
};
struct stPlayerPool {
	uint32_t					ulMaxPlayerID;
	uint16_t					sLocalPlayerID;
	void* 						pVTBL_txtHandler;
	std::string					strLocalPlayerName;
	struct stLocalPlayer*		pLocalPlayer;
	int							iLocalPlayerPing;
	int							iLocalPlayerScore;
	struct stRemotePlayer* 		pRemotePlayer[1004];
	int							iIsListed[1004];
	DWORD						dwPlayerIP[1004]; // always 0
};

enum EConnectMode {
	SAMP_CONNECT_UNKNOWN,
	SAMP_CONNECT_SERVER,
	SAMP_CONNECT_DEBUG
};

struct ServerData {
	EConnectMode connect = SAMP_CONNECT_UNKNOWN;
	std::string address;
	std::string port;
	std::string username;
	Query::Information info;
};


#pragma pack(pop)

class Samp {
private:
	uint32_t dwSAMP_Addr;
	struct stSAMP* SAMP;
public:
	ServerData srvData;
	Samp::Samp();

	bool Init();
	int iGS();

	stPlayerPool* GetPlayerPool();
	std::string GetServerIp();
	std::string GetServerName();

	bool readServerData(const char* cmdline);
};

extern Samp* pSamp;