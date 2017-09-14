#include "BSP.h"

BSP bsp;

BSP::BSP(void)
{
	pMapData = NULL;
	mapName = "";
	hFile = NULL;
	localPlayer = new CLocalPlayer();
	entity = new CEntity();
}

BSP::~BSP(void)
{
	if (pMapData != NULL)
		free(pMapData);
	if (hFile != NULL)
		CloseHandle(hFile);
	if (localPlayer != NULL)
		free(localPlayer);
	if (entity != NULL)
		free(entity);
	if (!mapName.empty())
		mapName.erase();
}

HANDLE BSP::loadFile(std::string path, DWORD &size)
{

	hFile = CreateFile(path.c_str(), GENERIC_READ, NULL, NULL, OPEN_ALWAYS, NULL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
		return false;

	size = GetFileSize(hFile, NULL);

	if (!size)
	{
		CloseHandle(hFile);
		return NULL;
	}
	else
		return hFile;
}

dheader_t* BSP::LoadBSP(const std::string& path) {

	if (hFile != NULL)
		CloseHandle(hFile);

	if (!(hFile = loadFile(path, size)))
		return NULL;

	if (pMapData != NULL)
		delete[] pMapData;

	pMapData = new BYTE[size];

	DWORD dwReadSize = NULL;

	if (!ReadFile(hFile, pMapData, size, &dwReadSize, NULL)) {
		CloseHandle(hFile);
		delete[] pMapData;
		pMapData = NULL;
		return nullptr;
	}

	fileData = (dheader_t*)pMapData;

	nodeLump = getNodeArray();
	planeLump = getPlaneArray();
	leafLump = getLeafArray();

	return (dheader_t*)pMapData;
}



dnode_t * BSP::getNodeArray(void)
{
	int offset = fileData->lumps[5].fileofs;
	byte * node = (byte*)fileData;
	node += offset;
	return (dnode_t*)node;
}

dplane_t * BSP::getPlaneArray(void)
{
	int offset = fileData->lumps[1].fileofs;
	byte * plane = (byte*)fileData;
	plane += offset;
	return (dplane_t*)plane;
}

dleaf_t * BSP::getLeafArray(void)
{
	int offset = fileData->lumps[10].fileofs;
	byte * leaf = (byte*)fileData;
	leaf += offset;
	return (dleaf_t*)leaf;
}

dleaf_t* BSP::GetLeafForPoint(Vector& point) {

	int node = 0;

	dnode_t* pNode;
	dplane_t* pPlane;

	float d = 0.0f;

	while (node >= 0) {
		pNode = &nodeLump[node];
		pPlane = &planeLump[pNode->planenum];

		d = (point.x * pPlane->normal.x + point.y * pPlane->normal.y + point.z * pPlane->normal.z) - pPlane->dist;

		node = (d > 0) ? pNode->children[0] : pNode->children[1];
	}

	return &leafLump[-node - 1];
}

bool BSP::IsVisible(Vector vStart, const Vector vEnd) {

	dheader_t* fileData = (dheader_t*)pMapData;
	Vector vDirection(vEnd - vStart);
	dleaf_t* pLeaf = nullptr;
	Vector vPoint = vEnd;

	int iStepCount = (int)(sqrt(vDirection.x * vDirection.x + vDirection.y *
		vDirection.y + vDirection.z * vDirection.z));

	vDirection.x /= iStepCount;
	vDirection.y /= iStepCount;
	vDirection.z /= iStepCount;

	while (iStepCount) {

		vPoint.x -= vDirection.x;
		vPoint.y -= vDirection.y;
		vPoint.z -= vDirection.z;

		pLeaf = GetLeafForPoint(vPoint);

		if (pLeaf) {
			if (pLeaf->contents > 0) {
				cout << pLeaf->contents << endl;
			}
			
			if (pLeaf->contents & CONTENTS_SOLID) {
				return false;
			}
		}
		iStepCount--;
	}

	return true;
}

void BSP::Main()
{
	while (true)
	{
		if (!localPlayer->InGame()) //if not in game make mapname empty again
		{
			if (strcmp(mapName.c_str(), "") != 0)
			{
				mapName[0] = '\0';
			}
		}
		else  //if we are in game and mapName is empty we need to update it
		{
			if (localPlayer->InGame() && mapName.empty())
			{
				mapName = localPlayer->GetMapName();

				char filename[MAX_PATH];
				if (GetModuleFileNameEx(Process.HandleProcess, NULL, filename, MAX_PATH) == 0) {
					return;
				}

				std::string tmp = filename;
				int pos = tmp.find("csgo");
				tmp = tmp.substr(0, pos);
				tmp = tmp + "csgo\\maps\\" + mapName + ".bsp";

				bsp.LoadBSP(tmp);
			}
		}
		Sleep(1000);
	}
	
}