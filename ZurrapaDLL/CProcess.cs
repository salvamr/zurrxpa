using System;
using System.Diagnostics;
using Binarysharp.MemoryManagement;
using Binarysharp.MemoryManagement.Modules;
using Binarysharp.MemoryManagement.Native;

namespace ZurrapaDLL
{
    class CProcess
    {
        private static readonly Process process = Process.GetProcessesByName("csgo")[0];
        private static readonly MemorySharp mem = new MemorySharp(process);
        private static ProcessModule myProcessModule;
        private static ProcessModule clientDll, engineDll;
        private static ProcessModuleCollection myProcessModuleCollection;

        public static IntPtr CLIENT
        {
            get
            {
                return clientDll.BaseAddress;
            }
        }

        public static IntPtr ENGINE
        {
            get
            {
                return engineDll.BaseAddress;
            }
        }

        public static bool IsModuleLoaded(string ModuleName)
        {
            bool loaded = false;

            try
            {
                myProcessModuleCollection = process.Modules;

                for (int j = 0; j < myProcessModuleCollection.Count; j++)
                {
                    myProcessModule = myProcessModuleCollection[j];

                    if (myProcessModule.ModuleName.Contains(ModuleName))
                    {
                        clientDll = myProcessModule;
                        loaded = true;
                        break;
                    }
                }
            }
            catch
            {
                loaded = false;
            }

            return loaded;
        }

        public static T Read<T>(IntPtr Address)
        {
            T read = mem.Read<T>(Address);
            return read;
        }

        public static void Write<T>(IntPtr Address, T value)
        {
            mem.Write<T>(Address, value);
        }
    }
}
