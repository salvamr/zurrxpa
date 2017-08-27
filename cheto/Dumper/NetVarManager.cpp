#include "HNetVarManager.h"
#include "HUtilis.h"

#include <iomanip>
#include <sstream>
#include <fstream>
#include <cstdint>
#include "../Process.h"

namespace Dumper
{
    namespace NetVarManager
    {
        RecvTable::RecvTable( const uintptr_t& base ) :
            CMemory( base, 0x10 )
        {
        }

        uintptr_t RecvTable::GetPropById( int id )
        {
            return Get<uintptr_t>() + id * 0x3C;
        }

        std::string RecvTable::GetTableName( void )
        {
            auto toReturn = std::string( "", 32 );
            dDumper->ReadMemory( Get<DWORD>( 0xC ), &toReturn.at( 0 ), 32 );
            return toReturn;
        }

        std::string RecvTable::GetClassNameA( void )
        {
            auto toReturn = GetTableName();
            toReturn.replace( toReturn.begin(), toReturn.begin() + 3, "C" );
            return toReturn;
        }

        int RecvTable::GetPropCount( void )
        {
            return Get<int>( 0x4 );
        }

        RecvProp::RecvProp( const uintptr_t& base, int level, int offset ) :
            CMemory( base, 0x3C ),
            _level( level ),
            _offset( offset )
        {
        }

        uintptr_t RecvProp::GetTable( void )
        {
            return Get<uintptr_t>( 0x28 );
        }

        std::string RecvProp::GetPropName( void )
        {
            auto toReturn = std::string( "", 64 );
            dDumper->ReadMemory( Get<DWORD>(), &toReturn.at( 0 ), 64 );
            return toReturn;
        }

        int RecvProp::GetPropOffset( void )
        {
            return _offset + Get<int>( 0x2C );
        }

        int RecvProp::GetPropType( void )
        {
            return Get<int>( 0x4 );
        }

        int RecvProp::GetPropElements( void )
        {
            return Get<int>( 0x34 );
        }

        int RecvProp::GetPropStringBufferCount()
        {
            return Get<int>( 0xC );
        }

        const int& RecvProp::GetLevel( void ) const
        {
            return _level;
        }

        ClientClass::ClientClass( const uintptr_t& base ) :
            CMemory( base, 0x28 )
        {
        }

        int ClientClass::GetClassId( void )
        {
            return Get<int>( 0x14 );
        }

        std::string ClientClass::GetClassNameA( void )
        {
            auto toReturn = std::string( "", 64 );
            dDumper->ReadMemory( Get<DWORD>( 0x8 ), &toReturn.at( 0 ), 64 );
            return toReturn;
        }

        uintptr_t ClientClass::GetNextClass( void )
        {
            return Get<uintptr_t>( 0x10 );
        }

        uintptr_t ClientClass::GetTable( void )
        {
            return Get<uintptr_t>( 0xC );
        }

        bool CNetVarManager::Load( void )
        {
			auto decalname = dDumper->FindPattern("client.dll", "64 65 63 61 6C 6E 61 6D 65 00", 0, 0, 0);
			
			std::stringstream ss;
			for (auto i = 0; i < 4; ++i)
			{
				ss << std::hex << std::setw(2) << std::setfill('0') << ((decalname >> 8 * i) & 0xFF) << " ";
			}

			auto decalref = dDumper->FindPattern("client.dll", ss.str().c_str(), Remote::SignatureType_t::NORMAL, 0, 0);

			decalref = dDumper->FindPatternSkip("client.dll", ss.str().c_str(), 5, 0xA, Remote::SignatureType_t::NORMAL, 0, 0);

			std::uint32_t firstclass;
			dDumper->ReadMemory(decalref + 0x3B, &firstclass, sizeof(firstclass));
			
			if (!firstclass)
				return false;

			for (auto Class = ClientClass(firstclass); Class.Get(); Class = ClientClass(Class.GetNextClass())) {

				auto table = RecvTable(Class.GetTable());
				if (!table.Get())
					continue;

				ScanTable(table, 0, 0, table.GetTableName().c_str());
			}
			return true;
        }

        void CNetVarManager::Release( void )
        {
            for( auto& table : _tables ) {
                for( auto& prop : table.second ) {
                    delete prop.second;
                }
                table.second.clear();
            }
            _tables.clear();
        }

        int CNetVarManager::GetNetVar( const std::string& tablename, const std::string& varname )
        {
            auto table = _tables.find( tablename );
            if( table != _tables.end() ) {
                for( auto& prop : table->second ) {
                    if( prop.first == varname )
                        return prop.second->GetPropOffset();
                }
            }
            return 0;
        }

        void CNetVarManager::ScanTable( RecvTable& table, int level, int offset, const char* name )
        {
            auto count = table.GetPropCount();
            for( auto i = 0; i < count; ++i ) {

                auto prop = new RecvProp( table.GetPropById( i ), level, offset );
                auto propName = prop->GetPropName();

                if( isdigit( propName[ 0 ] ) )
                    continue;

                auto isBaseClass = !strcmp( propName.c_str(), "baseclass" );
                if( !isBaseClass ) {
                    _tables[ name ].push_back( {
                        propName.c_str(), prop
                    } );
                }

                auto child = prop->GetTable();
                if( !child )
                    continue;

                auto recvTable = RecvTable( child );

                if( isBaseClass ) {
                    _tables[ name ].push_back( {
                        recvTable.GetTableName(), prop
                    } );
                    --level;
                }

                ScanTable( recvTable, ++level, prop->GetPropOffset(), name );
            }
        }

        CNetVarManager* CNetVarManager::Singleton( void )
        {
            static auto g_pNetVarManager = new CNetVarManager();
            return g_pNetVarManager;
        }
    }
}