using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Threading;

namespace ZurrapaDLL
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("hi");
            CProcess.waitingForGame("csgo");

            Console.WriteLine("client.dll: " + CProcess.CLIENT);

            //Threads.Do();
            Console.ReadLine();
           
        }
    }
}
