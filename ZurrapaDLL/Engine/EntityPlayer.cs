using Microsoft.Xna.Framework;
using System;
using System.Collections.Generic;
using ZurrapaDLL.ProcessManagement;

namespace ZurrapaDLL.Engine
{
    class EntityPlayer
    {
        private static EntityPlayer instance;

        private EntityPlayer() { }

        public static EntityPlayer Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new EntityPlayer();
                }

                return instance;
            }
        }

        public IntPtr GetEntity(int Index)
        {
            return CProcess.Read<IntPtr>(CProcess.Client.BaseAddress /*+ Offsets.m_deEntityList + (Index - 1) * 0x10*/);
        }

        public bool IsAlive(int Index)
        {
            return CProcess.Read<bool>(GetEntity(Index) /*+ Offsets.m_lifeState*/);
        }

        public bool IsInvisible(int Index)
        {
            return CProcess.Read<bool>(GetEntity(Index) /*+ Offsets.m_bGunGameImmunity*/);
        }

        public bool IsDormant(int Index)
        {
            return CProcess.Read<bool>(GetEntity(Index) /*+ Offsets.m_bDormant*/);
        }

        public int GetHealth(int Index)
        {
            return CProcess.Read<int>(GetEntity(Index) /*+ Offsets.m_iHealth*/);
        }

        public int GetTeam(int Index)
        {
            return CProcess.Read<int>(GetEntity(Index) /*+ Offsets.m_iTeamNum*/);
        }

        public IntPtr GetBoneMatrix(int Index)
        {
            return CProcess.Read<IntPtr>(GetEntity(Index) /*+ Offsets.m_dwBoneMatrix*/);
        }

        public List<int> GetMaxPlayers()
        {
            List<int> totalPlayers = new List<int>(0);

            var maxPlayers = CProcess.Read<int>(CProcess.Read<IntPtr>(CProcess.Engine.BaseAddress /*+ Offset.m_dwClientState*/) /*+ Offset.m_dwMaxPlayers*/);

            //Existe el player con indice 0 ???? XD
            for (int i = 0; i < maxPlayers; i++)
            {
                if (GetEntity(i) != null &&
                    !IsAlive(i) &&
                    !IsDormant(i) &&
                    GetBoneMatrix(i) != null &&
                    GetHealth(i) > 0 &&
                    !IsInvisible(i) &&
                    GetBone(i, 0 /*Settings.AimbotBone*/).Length() != 0)
                {
                    totalPlayers.Add(i);
                }
            }

            return totalPlayers;
        }

        public Vector3 GetBone(int Index, int BoneID)
        {
            return new Vector3
            {
                X = CProcess.Read<float>((IntPtr)GetBoneMatrix(Index) + 0x30 * BoneID + 0x0C),
                Y = CProcess.Read<float>((IntPtr)GetBoneMatrix(Index) + 0x30 * BoneID + 0x1C),
                Z = CProcess.Read<float>((IntPtr)GetBoneMatrix(Index) + 0x30 * BoneID + 0x2C)
            };
        }
    }
}
