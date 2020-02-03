using System;
using System.Diagnostics;
using Binarysharp.MemoryManagement;
using Binarysharp.MemoryManagement.Modules;
using ZurrapaDLL.Globals;

namespace ZurrapaDLL.ProcessManagement
{
    class CProcess
    {
        private static CProcess _instance;
        private MemorySharp mem;
        private static RemoteModule clientDll, engineDll;

        private CProcess()
        {
            mem = new MemorySharp(Process.GetProcessesByName(Global.GAME_NAME)[0].Id);
        }

        public static CProcess Instance
        {
            get
            {
                if (_instance == null)
                {
                    _instance = new CProcess();
                }

                return _instance;
            }
        }

        public bool IsGameReady()
        {
            try
            {
                clientDll = mem.Modules["client.dll"];
                engineDll = mem.Modules["engine.dll"];
                return true;
            } catch
            {
                return false;
            }
        }

        public void Close()
        {
            mem.Dispose();
        }

        public static RemoteModule Client
        {
            get
            {
                return clientDll;
            }
        }

        public static RemoteModule Engine
        {
            get
            {
                return engineDll;
            }
        }

        public T Read<T>(IntPtr Address)
        {
            T read = mem.Read<T>(Address);
            return read;
        }

        public void Write<T>(IntPtr Address, T value)
        {
            mem.Write<T>(Address, value);
        }

        public IntPtr FindPattern(string module, byte[] pattern, SignatureType signatureType, byte patternOffset, byte addressOffset)
        {
            var mod = mem.Modules[module];

            if (!mod.IsValid)
            {
                return IntPtr.Zero;
            }

            var pb = mod.Read<byte>(0);

            return IntPtr.Zero;
        }
    }
}
