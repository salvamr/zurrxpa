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
using ZurrapaDLL.Engine;

namespace ZurrapaDLL
{
    class Threads
    {
        private static Thread thDebugger;
        private static Thread thAimbot;
        private static Thread thTriggerbot;
        private static Thread thBunnyhop;
        private static Thread thMiscellaneous;

        public static void Do()
        {
            Aimbot oAimbot = new Aimbot();
            thAimbot = new Thread(new ThreadStart(oAimbot.Start));
            thAimbot.Start();
            thDebugger = new Thread(new ThreadStart(IsDebugger));
            thTriggerbot = new Thread(new ThreadStart(Triggerbot));
            thBunnyhop = new Thread(new ThreadStart(Bunnyhop));
            thMiscellaneous = new Thread(new ThreadStart(Miscellaneous));
        }

        public static void End()
        {
            thDebugger.Abort();
            thAimbot.Abort();
            thTriggerbot.Abort();
            thBunnyhop.Abort();
            thMiscellaneous.Abort();
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
                Thread.Sleep(1);
            }
        }

        private static void Triggerbot()
        {
            Triggerbot trigger = new Triggerbot();

            while (true)
            {
                trigger.Start();
                Thread.Sleep(1);
            }
        }

        private static void Bunnyhop()
        {
            Bunnyhop bunny = new Bunnyhop();

            while (true)
            {
                bunny.Start();
                Thread.Sleep(1);
            }
        }

        private static void Miscellaneous()
        {
            Miscellaneous misc = new Miscellaneous();

            while (true)
            {
                misc.Start();
                Thread.Sleep(1);
            }
        }

        private static void WeaponConfig()
        {
            WeaponConfig weaponcfg = new WeaponConfig();

            while (true)
            {
                weaponcfg.Start();
                Thread.Sleep(1);
            }
        }
        #endregion
    }
}
