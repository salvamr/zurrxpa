#ifndef _HOFFSETMANAGER_H_
#define _HOFFSETMANAGER_H_

#include "..\Include\HWin.h"
#include "..\Remote\HRemote.h"

namespace Dumper
{
    namespace OffsetManager
    {
        class COffsetManager
        {
        public:

            static void Dump( void );
            static COffsetManager* Singleton( void );
        };
    }
}

#ifndef pOffsetManager
#define pOffsetManager Dumper::OffsetManager::COffsetManager::Singleton( )
#endif

#endif /* _HOFFSETMANAGER_H_ */
