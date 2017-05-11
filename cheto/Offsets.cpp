#include "Offsets.h"
#include "HMain.h"
#include "Process.h"
#include "Printing.h"

COffsets Offset;

void COffsets::Load()
{
	Print.it("Dumping offsets ...");

	if (!pProcess->Attach( "csgo.exe" )) 
	{
		Print.error("Failed to attach Zurrapa Dumper");
	} 

	pNetVarManager->Load();
	pOffsetManager->Dump();

	delete pOffsetManager;

	pNetVarManager->Release();
	delete pNetVarManager;

	pProcess->Detach();
	delete pProcess;
}