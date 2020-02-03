using System;
using ZurrapaDLL.ProcessManagement;

namespace ZurrapaDLL.Engine
{
    class LocalPlayer
    {
        private LocalPlayer instance;

        private LocalPlayer() { }

        public LocalPlayer Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new LocalPlayer();
                }

                return instance;
            }
        }

        public IntPtr GetPlayer()
        {
            return CProcess.Read<IntPtr>(CProcess.Client.BaseAddress + 0xAB0708);
        }

        public bool IsShooting()
        {
            return CProcess.Read<bool>(GetPlayer() /*+ Offsets.m_iShotsFired*/);
        }

        public int GetPlayerStatus()
        {
            return CProcess.Read<int>(GetPlayer() /*+ Offsets.m_fFlags*/);
        }

        public int GetHealth()
        {
            return CProcess.Read<int>(GetPlayer() + 0xFC);
        }

        public int GetCrosshairID()
        {
            return CProcess.Read<int>(GetPlayer() /*+ Offsets.m_iCrossHairID*/);
        }

        public unsafe float GetSentivity()
        {
            ulong sens_ptr = (ulong)CProcess.Client.BaseAddress /*+ Offsets.m_pSensitivity*/;
            ulong sens_value_xored = CProcess.Read<ulong>(CProcess.Client.BaseAddress /*+ Offsets.m_dwSensitivity*/);
            ulong Value = sens_ptr ^ sens_value_xored;
            return *(float*)&Value;
        }

        public unsafe void SetSensitivity()
        {

        }
    }
}
