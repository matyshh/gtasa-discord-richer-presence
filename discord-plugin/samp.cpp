#include "samp.h"

Samp* pSamp;

Samp::Samp()
{
	dwSAMP_Addr = NULL;
	stSAMP* SAMP = nullptr;
}

bool Samp::Init()
{
	if (dwSAMP_Addr == NULL) dwSAMP_Addr = (DWORD)GetModuleHandleA("samp.dll");
	if (dwSAMP_Addr == NULL) return false;

	if (SAMP == nullptr) SAMP = *(stSAMP**)(dwSAMP_Addr + 0x215B40);
	if (SAMP == nullptr) return false;

	if (SAMP->iGameState != 14) return false;

	return true;
}

stPlayerPool* Samp::GetPlayerPool()
{
	return SAMP->pPools->pPlayer;
}

std::string Samp::GetServerIp()
{
	return SAMP->szIP;
}

std::string Samp::GetServerName()
{
	return SAMP->szHostname;
}