﻿#include "Offsets.h"
#include "Dumper\HMain.h"
#include "Printing.h"

COffsets Offset;

void COffsets::Load()
{
	Print::it("Dumping offsets ...");

	if (!dDumper->Start())
	{
		Print::error("Failed to start the dumper");
	}

	pNetVarManager->Load();
	pOffsetManager->Dump();

	delete pOffsetManager;

	pNetVarManager->Release();
	delete pNetVarManager;
}