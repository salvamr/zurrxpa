using System;
using System.Management;

namespace ZurrapaLoader.HardwareIDManagement
{
    class HardwareIDInfo
    {
        public static string GetCPU()
        {
            //https://msdn.microsoft.com/en-us/library/aa394084(v=vs.85).aspx
            string result = string.Empty;//creating a empty string
            using (ManagementClass mgBoard = new ManagementClass("Win32_BaseBoard"))
            using (ManagementClass mgProcessor = new ManagementClass("Win32_BaseBoard"))
            {
                foreach (ManagementObject mob in mgBoard.GetInstances())//having a foreach loop
                {
                    Console.WriteLine(mob.GetPropertyValue("Product").ToString());
                }
            }
            return result;
        }

        public static string GetGPU()
        {
            return "";
        }
        
        public static string GetMOBO()
        {
            return "";
        }

    }
}
