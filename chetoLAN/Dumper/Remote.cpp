#include "HRemote.h"

namespace Dumper
{
    namespace Remote
    {
        CMemory::CMemory( const uintptr_t& base, const size_t& size ) :
            _base( base )
        {
            _bytes = vecByte( size );
            if( !_base || !dDumper->ReadMemory( _base, static_cast< void* >( &_bytes.at( 0 ) ), size ) ) {
                _bytes = vecByte( 0 );
            }
        }

        CMemory::~CMemory( void )
        {
            if( !_bytes.empty() ) {
                _bytes.clear();
            }
        }

        const uintptr_t& CMemory::Get( void ) const
        {
            return _base;
        }

        CModule::CModule( const std::string& name, const uintptr_t& imgsize, const intptr_t& imgbase ) :
            _name( name ),
            _imgsize( imgsize ),
            _imgbase( imgbase )
        {
            _bytes = vecByte( imgsize );
            dDumper->ReadMemory( _imgbase, &_bytes[ 0 ], _imgsize );
        }

        CModule::~CModule( void )
        {
            if( !_bytes.empty() ) {
                _bytes.clear();
            }
        }

        uintptr_t CModule::operator+( uintptr_t offset ) const
        {
            return _imgbase + offset;
        }

        uintptr_t CModule::operator-( uintptr_t offset ) const
        {
            return _imgbase - offset;
        }

        const std::string& CModule::GetName() const
        {
            return _name;
        }

        const uintptr_t& CModule::GetImgSize() const
        {
            return _imgsize;
        }

        const uintptr_t& CModule::GetImgBase() const
        {
            return _imgbase;
        }

        const vecByte& CModule::GetDumpedBytes() const
        {
            return _bytes;
        }

		bool CProcess::Start()
		{
			if (!GetProcessHandle(Process.HandleProcess))
				return false;

			if (!GetProcessModules())
				return false;
			
			return true;
		}

        bool CProcess::ReadMemory( const uintptr_t& address, void* pBuffer, size_t size ) const
        {
            return bool( ReadProcessMemory( _hproc, LPCVOID( address ), pBuffer, size, nullptr ) == TRUE );
        }

        bool CProcess::WriteMemory( uintptr_t& address, const void* pBuffer, size_t size ) const
        {
            return bool( WriteProcessMemory( _hproc, LPVOID( address ), pBuffer, size, nullptr ) == TRUE );
        }

        bool CProcess::CompareBytes( const unsigned char* bytes, const char* pattern )
        {
            for( ; *pattern; *pattern != ' ' ? ++bytes : bytes, ++pattern ) {
                if( *pattern == ' ' || *pattern == '?' )
                    continue;
                if( *bytes != getByte( pattern ) )
                    return false;
                ++pattern;
            }
            return true;
        }

        uintptr_t CProcess::FindPattern( const std::string& module, const char* pattern, short type, uintptr_t patternOffset, uintptr_t addressOffset )
        {
            auto mod = GetModuleByName( module );
            if( !mod )
                return 0;

            auto pb = const_cast< unsigned char* >( &mod->GetDumpedBytes().at( 0 ) );
            auto max = mod->GetImgSize() - 0x1000;

            for( auto off = 0UL; off < max; ++off ) {
                if( CompareBytes( pb + off, pattern ) ) {

                    auto add = mod->GetImgBase() + off + patternOffset;

                    if( type & SignatureType_t::READ )
                        ReadMemory( add, &add, sizeof( uintptr_t ) );

                    if( type & SignatureType_t::SUBTRACT )
                        add -= mod->GetImgBase();

                    return add + addressOffset;
                }
            }
            return 0;
        }

		uintptr_t CProcess::FindPatternSkip(const std::string& module, const char* pattern, int skips, DWORD skip_size, short type, uintptr_t patternOffset, uintptr_t addressOffset)
		{
			auto mod = GetModuleByName(module);
			if (!mod)
				return 0;

			auto pb = const_cast< unsigned char* >(&mod->GetDumpedBytes().at(0));
			auto max = mod->GetImgSize() - 0x1000;

			for (auto off = 0UL; off < max; ++off) {
				if (CompareBytes(pb + off, pattern)) {
					static int iSkip = 0;
					if (iSkip < skips)
					{
						off += skip_size;
						iSkip++;
						continue;
					}
					auto add = mod->GetImgBase() + off + patternOffset;

					if (type & SignatureType_t::READ)
						ReadMemory(add, &add, sizeof(uintptr_t));

					if (type & SignatureType_t::SUBTRACT)
						add -= mod->GetImgBase();

					return add + addressOffset;
				}
			}
			return 0;
		}

        bool CProcess::GetProcessHandle( HANDLE proc )
        {
            return bool( ( _hproc = proc ) != nullptr );
        }

        bool CProcess::GetProcessModules( void )
        {
			try
			{
				_moduleInfo[0] = Process.GetModuleInfo(Process.Client);
				_moduleInfo[1] = Process.GetModuleInfo(Process.Engine);
				_modules["client.dll"] = new CModule("client.dll", uintptr_t(_moduleInfo[0].SizeOfImage), uintptr_t(_moduleInfo[0].lpBaseOfDll));
				_modules["engine.dll"] = new CModule("engine.dll", uintptr_t(_moduleInfo[1].SizeOfImage), uintptr_t(_moduleInfo[1].lpBaseOfDll));
				return true;
			}
			catch (int)
			{
				return false;
			}
        }

        CModule* CProcess::GetModuleByName( const std::string& name )
        {
			if (name.compare("client.dll") == 0)
			{
				return (_modules["client.dll"]);
			}
			if (name.compare("engine.dll") == 0)
			{
				return (_modules["engine.dll"]);
			}
			return nullptr;
        }

        CProcess* CProcess::Singleton( void )
        {
            static auto g_pProcess = new CProcess();
            return g_pProcess;
        }
    }
}
