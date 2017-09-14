#ifndef _h_bsp
#define _h_bsp

#include <Windows.h>
#include <string>

#include "Include.h"

//Stolen from SDK
#define	HEADER_LUMPS					64
#define	MAX_MAP_NODES					65536
#define	MAX_MAP_PLANES					65536
#define	MAX_MAP_LEAFS					65536

#define	CONTENTS_SOLID			0x1		// an eye is never valid in a solid
#define	CONTENTS_WINDOW			0x2		// translucent, but not watery (glass)
#define	CONTENTS_AUX			0x4
#define	CONTENTS_GRATE			0x8		// alpha-tested "grate" textures.  Bullets/sight pass through, but solids don't
#define	CONTENTS_SLIME			0x10
#define	CONTENTS_WATER			0x20
#define	CONTENTS_BLOCKLOS		0x40	// block AI line of sight
#define CONTENTS_OPAQUE			0x80	// things that cannot be seen through (may be non-solid though)
#define CONTENTS_MOVEABLE		0x4000
#define	CONTENTS_MONSTER		0x2000000	// should never be on a brush, only in game
#define	CONTENTS_PLAYERCLIP		0x10000
#define	CONTENTS_MONSTERCLIP	0x20000
#define CONTENTS_IGNORE_NODRAW_OPAQUE	0x2000
#define	CONTENTS_DEBRIS			0x4000000
#define CONTENTS_HITBOX			0x40000000	// use accurate hitboxes on trace

#define	MASK_SOLID					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// everything that blocks player movement
#define	MASK_PLAYERSOLID			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// blocks npc movement
#define	MASK_NPCSOLID				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// water physics in these contents
#define	MASK_WATER					(CONTENTS_WATER|CONTENTS_MOVEABLE|CONTENTS_SLIME)
// everything that blocks lighting
#define	MASK_OPAQUE					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_OPAQUE)
// everything that blocks lighting, but with monsters added.
#define MASK_OPAQUE_AND_NPCS		(MASK_OPAQUE|CONTENTS_MONSTER)
// everything that blocks line of sight for AI
#define MASK_BLOCKLOS				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_BLOCKLOS)
// everything that blocks line of sight for AI plus NPCs
#define MASK_BLOCKLOS_AND_NPCS		(MASK_BLOCKLOS|CONTENTS_MONSTER)
// everything that blocks line of sight for players
#define	MASK_VISIBLE					(MASK_OPAQUE|CONTENTS_IGNORE_NODRAW_OPAQUE)
// everything that blocks line of sight for players, but with monsters added.
#define MASK_VISIBLE_AND_NPCS		(MASK_OPAQUE_AND_NPCS|CONTENTS_IGNORE_NODRAW_OPAQUE)
// bullets see these as solid
#define	MASK_SHOT					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)
// non-raycasted weapons see this as solid (includes grates)
#define MASK_SHOT_HULL				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_GRATE)
// hits solids (not grates) and passes through everything else
#define MASK_SHOT_PORTAL			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER)
// everything normally solid, except monsters (world+brush only)
#define MASK_SOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_GRATE)
// everything normally solid for player movement, except monsters (world+brush only)
#define MASK_PLAYERSOLID_BRUSHONLY	(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_PLAYERCLIP|CONTENTS_GRATE)
// everything normally solid for npc movement, except monsters (world+brush only)
#define MASK_NPCSOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
// just the world, used for route rebuilding
#define MASK_NPCWORLDSTATIC			(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
// These are things that can split areaportals
#define MASK_SPLITAREAPORTAL		(CONTENTS_WATER|CONTENTS_SLIME)

struct dnode_t
{
	int		planenum;	// index into plane array
	int		children[2];	// negative numbers are -(leafs + 1), not nodes
	short		mins[3];	// for frustum culling
	short		maxs[3];
	unsigned short	firstface;	// index into face array
	unsigned short	numfaces;	// counting both sides
	short		area;		// If all leaves below this node are in the same area, then
							// this is the area index. If not, this is -1.
	short		paddding;	// pad to 32 bytes length
};

struct dleaf_t
{
	int			contents;		// OR of all brushes (not needed?)
	short			cluster;		// cluster this leaf is in
	short			area : 9;			// area this leaf is in
	short			flags : 7;		// flags
	short			mins[3];		// for frustum culling
	short			maxs[3];
	unsigned short		firstleafface;		// index into leaffaces
	unsigned short		numleaffaces;
	unsigned short		firstleafbrush;		// index into leafbrushes
	unsigned short		numleafbrushes;
	short			leafWaterDataID;	// -1 for not in water

										//!!! NOTE: for maps of version 19 or lower uncomment this block
										/*
										CompressedLightCube	ambientLighting;	// Precaculated light info for entities.
										short			padding;		// padding to 4-byte boundary
										*/
};


struct dplane_t
{
	Vector	normal;	// normal vector
	float	dist;	// distance from origin
	int	type;	// plane axis identifier
};

struct lump_t
{
	int		fileofs, filelen;
	int		version;		// default to zero
	char	fourCC[4];		// default to ( char )0, ( char )0, ( char )0, ( char )0
};

struct dheader_t
{
	int	ident;                // BSP file identifier
	int	version;              // BSP file version
	lump_t	lumps[HEADER_LUMPS];  // lump directory array
	int	mapRevision;          // the map's revision (iteration, version) number
};


class BSP {

public:

	BSP(void);
	~BSP(void);

	dheader_t* LoadBSP(const std::string& path);

	dnode_t * getNodeArray(void);

	dplane_t * getPlaneArray(void);

	dleaf_t * getLeafArray(void);

	dleaf_t* GetLeafForPoint(Vector& point);

	bool IsVisible(Vector vStart, const Vector vEnd);

	HANDLE loadFile(std::string path, DWORD &size);

	void Main();

private:
	byte * pMapData;
	string mapName;
	DWORD size;
	HANDLE hFile;
	dheader_t * fileData;

	dnode_t * nodeLump;
	dplane_t * planeLump;
	dleaf_t * leafLump;

	CLocalPlayer* localPlayer;
	CEntity* entity;
}; extern BSP bsp;
#endif