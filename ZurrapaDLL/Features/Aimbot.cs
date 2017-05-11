using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using ZurrapaDLL.Engine;

namespace ZurrapaDLL.Features
{
    class Aimbot
    {
        public Aimbot()
        {

        }

        public void Start()
        {
            while(true)
            {
                Console.WriteLine(LocalPlayer.GetHealth());
                Thread.Sleep(100);
            }
        }
    }
}
