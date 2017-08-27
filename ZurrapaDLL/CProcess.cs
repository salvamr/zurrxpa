using System;
using System.Diagnostics;
using System.Collections;
using System.Threading;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using Binarysharp.MemoryManagement;
using Binarysharp.MemoryManagement.Modules;
using Binarysharp.MemoryManagement.Native;

namespace ZurrapaDLL
{
    class CProcess
    {
        private static MemorySharp mem;
        private static RemoteModule clientDll, engineDll;

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

        public static void waitingForGame(string procName)
        {
            do
            {
                if (isProcessReady(procName))
                {
                    clientDll = findModulePointer("client.dll");
                    engineDll = findModulePointer("engine.dll");
                }
                
                Thread.Sleep(1000);
            } while (clientDll.Equals(IntPtr.Zero) && engineDll.Equals(IntPtr.Zero));
        }

        private static bool isProcessReady(string procName)
        {
            try
            {
                mem = new MemorySharp(Process.GetProcessesByName(procName)[0].Id);
                return true;
            }
            catch (Exception)
            {
                isProcessReady(procName);
                return false;
            }
        }

        private static RemoteModule findModulePointer(string moduleName)
        {
            return mem.Modules[moduleName];
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

        [DllImport("user32.dll")]
        private static extern int FindWindow(string sClass, string sWindow);
    }
}
