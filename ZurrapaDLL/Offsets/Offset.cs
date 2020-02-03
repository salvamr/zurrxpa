using System;
using ZurrapaDLL.ProcessManagement;

namespace ZurrapaDLL.Offsets
{
    class Offset
    {
        public static IntPtr m_iItemDefinitionIndex { get; private set; }
        public static IntPtr m_vecOrigin { get; private set; }
        public static IntPtr m_iTeamNum { get; private set; }
        public static IntPtr m_bGunGameImmunity { get; private set; }
        public static IntPtr m_iCrossHairID { get; private set; }
        public static IntPtr m_iShotsFired { get; private set; }
        public static IntPtr m_vecVelocity { get; private set; }
        public static IntPtr m_lifeState { get; private set; }
        public static IntPtr m_fFlags { get; private set; }
        public static IntPtr m_iHealth { get; private set; }
        public static IntPtr m_hActiveWeapon { get; private set; }
        public static IntPtr m_vecViewOffset { get; private set; }
        public static IntPtr m_vecPunch { get; private set; }
        public static IntPtr m_dwBoneMatrix { get; private set; }
        public static IntPtr m_bDormant => (IntPtr)0xE9;
        public static IntPtr m_dwLocalPlayer { get; private set; }
        public static IntPtr m_dwEntityList { get; private set; }
        public static IntPtr m_dwForceJump { get; private set; }
        public static IntPtr m_dwForceAttack { get; private set; }
        public static IntPtr m_pSensitivity { get; private set; }
        public static IntPtr m_dwSensitivity { get; private set; }
        public static IntPtr m_dwClientState { get; private set; }
        public static IntPtr m_dwViewAngles { get; private set; }
        public static IntPtr m_dwMaxPlayers { get; private set; }
        public static IntPtr dwClientState_State { get; private set; }
        public static IntPtr dwMouseEnable { get; private set; }
        public static IntPtr dwMouseEnablePtr { get; private set; }

        //public static bool Dump()
        //{
            
        //    byte[] LocalPlayerSig = { 0xA3, 0x00, 0x00, 0x00, 0x00, 0xC7, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x59, 0xC3, 0x6A, 0x00};
        //    string LocalPlayerMask = "x????xx????????x????xxx?";
        //    //A3 ? ? ? ? C7 05 ? ? ? ? ? ? ? ? E8 ? ? ? ? 59 C3 6A ?
        //    m_dwLocalPlayer = sigScan.FindPattern(LocalPlayerSig, LocalPlayerMask, 2);
        //}


    }
}
