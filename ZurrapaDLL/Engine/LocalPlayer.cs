using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ZurrapaDLL.Engine
{
    class LocalPlayer
    {
        protected static IntPtr GetPlayer()
        {
            return CProcess.Read<IntPtr>(CProcess.CLIENT /*+ Offsets.m_dwLocalPlayer*/);
        }

        protected static bool IsShooting()
        {
            return CProcess.Read<bool>(GetPlayer() /*+ Offsets.m_iShotsFired*/);
        }

        protected static int GetPlayerStatus()
        {
            return CProcess.Read<int>(GetPlayer() /*+ Offsets.m_fFlags*/);
        }

        protected static int GetHealth()
        {
            return CProcess.Read<int>(GetPlayer() /*+ Offsets.m_iHealth*/);
        }

        protected static int GetCrosshairID()
        {
            return CProcess.Read<int>(GetPlayer() /*+ Offsets.m_iCrossHairID*/);
        }

        protected static unsafe float GetSentivity()
        {
            ulong sens_ptr = (ulong)CProcess.CLIENT /*+ Offsets.m_pSensitivity*/;
            ulong sens_value_xored = CProcess.Read<ulong>(CProcess.CLIENT /*+ Offsets.m_dwSensitivity*/);
            ulong Value = sens_ptr ^ sens_value_xored;
            return *(float*)&Value;
        }

        protected static unsafe void SetSensitivity()
        {

        }
    }
}
