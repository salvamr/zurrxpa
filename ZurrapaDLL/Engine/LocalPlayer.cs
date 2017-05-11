using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ZurrapaDLL.Engine
{
    static class LocalPlayer
    {

        public static IntPtr GetPlayer()
        {
            return CProcess.Read<IntPtr>(CProcess.CLIENT + 0xAB0708);
        }

        public static bool IsShooting()
        {
            return CProcess.Read<bool>(GetPlayer() /*+ Offsets.m_iShotsFired*/);
        }

        public static int GetPlayerStatus()
        {
            return CProcess.Read<int>(GetPlayer() /*+ Offsets.m_fFlags*/);
        }

        public static int GetHealth()
        {
            return CProcess.Read<int>(GetPlayer() + 0xFC);
        }

        public static int GetCrosshairID()
        {
            return CProcess.Read<int>(GetPlayer() /*+ Offsets.m_iCrossHairID*/);
        }

        public static unsafe float GetSentivity()
        {
            ulong sens_ptr = (ulong)CProcess.CLIENT /*+ Offsets.m_pSensitivity*/;
            ulong sens_value_xored = CProcess.Read<ulong>(CProcess.CLIENT /*+ Offsets.m_dwSensitivity*/);
            ulong Value = sens_ptr ^ sens_value_xored;
            return *(float*)&Value;
        }

        public static unsafe void SetSensitivity()
        {

        }
    }
}
