using System;
using ZurrapaDLL.Utils;
using ZurrapaDLL.Offsets;
using ZurrapaDLL.ProcessManagement;
using System.Threading;

namespace ZurrapaDLL
{
    class Program
    {
        static void Main(string[] args)
        {

            while (!CProcess.Instance.IsGameReady())
                Thread.Sleep(1000);

            Console.WriteLine("client.dll: " + CProcess.Client.BaseAddress);
            CProcess.Instance.FindPattern("client.dll", new byte[] { 0xA3, 0x00, 0x00, 0x00, 0x00, 0xC7, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x59, 0xC3, 0x6A, 0x00 }, SignatureType.SUBTRACT, 0, 0);

            //Threads.Do();
            Console.ReadLine();
        }
    }
}
