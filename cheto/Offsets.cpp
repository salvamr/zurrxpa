#include "Offsets.h"
#include "Dumper\HMain.h"
#include "Process.h"
#include "Printing.h"

COffsets Offset;

void COffsets::Load()
{
	Print.it("Dumping offsets ...");

	if (!dDumper->Start())
	{
		MessageBox(NULL, "Failed to start the dumper", "Zurrapa", MB_ICONERROR | MB_OK);
		CloseHandle(Process.HandleProcess);
		ExitProcess(0);
	}

	pNetVarManager->Load();
	pOffsetManager->Dump();

	delete pOffsetManager;

	pNetVarManager->Release();
	delete pNetVarManager;
}