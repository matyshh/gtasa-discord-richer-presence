#include "samp.h"
#include <memory>

Samp* pSamp;

Samp::Samp() {
	dwSAMP_Addr = NULL;
	stSAMP* SAMP = nullptr;
}

bool Samp::Init() {
	if (dwSAMP_Addr == NULL) dwSAMP_Addr = (DWORD)GetModuleHandleA("samp.dll");
	if (dwSAMP_Addr == NULL) return false;

	if (SAMP == nullptr) SAMP = *(stSAMP**)(dwSAMP_Addr + 0x215B40);
	if (SAMP == nullptr) return false;

	//if (SAMP->iGameState != 14) return false;

	return true;
}

int Samp::iGS() {
	return SAMP->iGameState;
}

bool Samp::readServerData(const char* cmdline) {
	auto input = std::unique_ptr<char>(_strdup(cmdline));
	char* next = nullptr;
	char* token = strtok_s(input.get(), " ", &next);
	while (token != nullptr) {
		if (!std::strcmp(token, "-c")) {
			if (srvData.connect != SAMP_CONNECT_UNKNOWN) {
				return false;
			}
			srvData.connect = SAMP_CONNECT_SERVER;
		}
		else if (!std::strcmp(token, "-d")) {
			if (srvData.connect != SAMP_CONNECT_UNKNOWN) {
				return false;
			}
			srvData.connect = SAMP_CONNECT_DEBUG;
		}
		else if (!std::strcmp(token, "-h")) {
			if (!next) {
				return false;
			}
			srvData.address = strtok_s(nullptr, " ", &next);
		}
		else if (!std::strcmp(token, "-p")) {
			if (!next) {
				return false;
			}
			srvData.port = strtok_s(nullptr, " ", &next);
		}
		else if (!std::strcmp(token, "-n")) {
			if (!next) {
				return false;
			}
			srvData.username = strtok_s(nullptr, " ", &next);
		}
		token = strtok_s(nullptr, " ", &next);
	}

	return true;
}


stPlayerPool* Samp::GetPlayerPool() {
	return SAMP->pPools->pPlayer;
}

std::string Samp::GetServerIp() {
	return SAMP->szIP;
}

std::string Samp::GetServerName() {
	return SAMP->szHostname;
}