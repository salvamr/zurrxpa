#include "Offsets.h"
#include "HMain.h"

#include "Process.h"

COffsets Offset;

void COffsets::Load()
{
	pProcess->Attach("csgo.exe");

	pNetVarManager->Load();
	pOffsetManager->Dump();

	delete pOffsetManager;

	pNetVarManager->Release();
	delete pNetVarManager;

	pProcess->Detach();
	delete pProcess;
}