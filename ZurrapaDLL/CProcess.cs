using System;
using System.Diagnostics;
using Binarysharp.MemoryManagement;
using Binarysharp.MemoryManagement.Modules;
using Binarysharp.MemoryManagement.Native;

namespace ZurrapaDLL
{
    class CProcess
    {
        public Process process;
        public ProcessModule myProcessModule, clientDll, engineDll;
        public ProcessModuleCollection myProcessModuleCollection;

        public CProcess(string procName)
        {
            try
            {
                process = Process.GetProcessesByName(procName)[0];

                myProcessModule = null;
                clientDll = null;
                engineDll = null;
            }
            catch (Exception e)
            {
                Console.WriteLine("{0}: {1}", procName.ToUpper(), e.Message);
            }
            finally
            {
                Environment.Exit(0);
            }
        }

        public bool IsModuleLoaded(string ModuleName)
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

        public T Read<T>(IntPtr Address)
        {
            MemorySharp mem = new MemorySharp(process);
            T read = mem.Read<T>(Address);
            return read;
        }

        public void Write<T>(IntPtr Address, T value)
        {
            MemorySharp mem = new MemorySharp(process);
            mem.Write<T>(Address, value);
        }
    }
}
