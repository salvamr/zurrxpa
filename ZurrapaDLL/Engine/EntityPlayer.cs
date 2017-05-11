using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media.Media3D;

namespace ZurrapaDLL.Engine
{
    class EntityPlayer
    {
        protected static IntPtr GetEntity(int Index)
        {
            return CProcess.Read<IntPtr>(CProcess.CLIENT /*+ Offsets.m_deEntityList + (Index - 1) * 0x10*/);
        }

        protected static bool IsAlive(int Index)
        {
            return CProcess.Read<bool>(GetEntity(Index) /*+ Offsets.m_lifeState*/);
        }

        protected static bool IsInvisible(int Index)
        {
            return CProcess.Read<bool>(GetEntity(Index) /*+ Offsets.m_bGunGameImmunity*/);
        }

        protected static bool IsDormant(int Index)
        {
            return CProcess.Read<bool>(GetEntity(Index) /*+ Offsets.m_bDormant*/);
        }

        protected static int GetHealth(int Index)
        {
            return CProcess.Read<int>(GetEntity(Index) /*+ Offsets.m_iHealth*/);
        }

        protected static int GetTeam(int Index)
        {
            return CProcess.Read<int>(GetEntity(Index) /*+ Offsets.m_iTeamNum*/);
        }

        protected static ulong GetBoneMatrix(int Index)
        {
            return CProcess.Read<ulong>(GetEntity(Index) /*+ Offsets.m_dwBoneMatrix*/);
        }

        protected static Vector3D GetBone(int Index, int BoneID)
        {
            Vector3D temp = new Vector3D();

            temp.X = CProcess.Read<double>((IntPtr)GetBoneMatrix(Index) + 0x30 * BoneID + 0x0C);
            temp.Y = CProcess.Read<double>((IntPtr)GetBoneMatrix(Index) + 0x30 * BoneID + 0x1C);
            temp.Z = CProcess.Read<double>((IntPtr)GetBoneMatrix(Index) + 0x30 * BoneID + 0x2C);

            return temp;
        }
    }
}
