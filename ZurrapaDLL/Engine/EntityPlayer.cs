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
        private static IntPtr EntityList;

        protected static void GetEntity(int Index)
        {
            EntityList = CProcess.Read<IntPtr>(CProcess.CLIENT /*+ Offsets.m_deEntityList + (Index - 1) * 0x10*/);
        }

        protected static bool IsAlive()
        {
            return CProcess.Read<bool>(EntityList /*+ Offsets.m_lifeState*/);
        }

        protected static bool IsInvisible()
        {
            return CProcess.Read<bool>(EntityList /*+ Offsets.m_bGunGameImmunity*/);
        }

        protected static bool IsDormant()
        {
            return CProcess.Read<bool>(EntityList /*+ Offsets.m_bDormant*/);
        }

        protected static int GetHealth()
        {
            return CProcess.Read<int>(EntityList /*+ Offsets.m_iHealth*/);
        }

        protected static int GetTeam()
        {
            return CProcess.Read<int>(EntityList /*+ Offsets.m_iTeamNum*/);
        }

        protected static ulong GetBoneMatrix()
        {
            return CProcess.Read<ulong>(EntityList /*+ Offsets.m_dwBoneMatrix*/);
        }

        protected static Vector3D GetBone(int BoneID)
        {
            Vector3D temp = new Vector3D();

            temp.X = CProcess.Read<double>((IntPtr)GetBoneMatrix() + 0x30 * BoneID + 0x0C);
            temp.Y = CProcess.Read<double>((IntPtr)GetBoneMatrix() + 0x30 * BoneID + 0x1C);
            temp.Z = CProcess.Read<double>((IntPtr)GetBoneMatrix() + 0x30 * BoneID + 0x2C);

            return temp;
        }
    }
}
