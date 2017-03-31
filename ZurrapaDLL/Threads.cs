using System;
using System.Threading;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ZurrapaDLL.Features;

namespace ZurrapaDLL
{
    class Threads
    {
        public static void Do()
        {
            Thread thDebugger       = new Thread(new ThreadStart(IsDebugger));
            Thread thAimbot         = new Thread(new ThreadStart(Aimbot));
            Thread thTriggerbot     = new Thread(new ThreadStart(Triggerbot));
            Thread thBunnyhop       = new Thread(new ThreadStart(Bunnyhop));
            Thread thMiscellaneous  = new Thread(new ThreadStart(Miscellaneous));
        }

        private static void IsDebugger()
        {
            while (true)
            {
                Thread.Sleep(20);

                if (Debugger.IsAttached)
                {
                    string temppath, current_path;

                    temppath = Path.Combine(Path.GetTempPath(), "autoDeleter.bat");
                    current_path = Path.Combine(Directory.GetCurrentDirectory(), Assembly.GetExecutingAssembly().GetName().Name + ".exe");

                    using (StreamWriter w = new StreamWriter(temppath))
                    {
                        w.WriteLine(":Repeat");
                        w.WriteLine("del \"" + current_path + "\"");
                        w.WriteLine("if exist \"" + current_path + "\" goto Repeat");
                        w.WriteLine("rmdir \"" + Directory.GetCurrentDirectory() + "\"");
                        w.WriteLine("del \"" + temppath + "\"");
                        w.Close();
                    }

                    using (Process proc = new Process())
                    {
                        proc.StartInfo.CreateNoWindow = true;
                        proc.StartInfo.WindowStyle = ProcessWindowStyle.Hidden;
                        proc.StartInfo.FileName = temppath;
                        proc.Start();
                    }

                    Environment.Exit(0);
                }
            }
        }

        #region Thread_Features
        private static void Aimbot()
        {
            Aimbot aim = new Aimbot();

            while (true)
            {
                aim.Start();
            }
        }

        private static void Triggerbot()
        {
            Triggerbot trigger = new Triggerbot();

            while(true)
            {
                trigger.Start();
            }
        }

        private static void Bunnyhop()
        {
            Bunnyhop bunny = new Bunnyhop();

            while(true)
            {
                bunny.Start();
            }
        }

        private static void Miscellaneous()
        {
            Miscellaneous misc = new Miscellaneous();

            while(true)
            {
                misc.Start();
            }
        }

        private static void WeaponConfig()
        {
            WeaponConfig weaponcfg = new WeaponConfig();

            while(true)
            {
                weaponcfg.Start();
            }
        }
        #endregion
    }
}
