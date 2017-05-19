#ifndef _SECURE_H_
#define _SECURE_H_

#include "Include.h"

class CSecure
{
public:
	CSecure();
	~CSecure();

	void	SteamCheck();
	void	LookingForCSGO();
	void	LookingForModules();

	bool	CheckSubcription();
	void	DeleteCheat();

	DWORD	serialNumber;

	string	TimeNow();

private:
	TCHAR	szFile[MAX_PATH];
	TCHAR	szCmd[MAX_PATH];

}; extern CSecure* Secure;

#endif
