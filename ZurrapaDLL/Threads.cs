using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace ZurrapaDLL
{
    class Threads
    {
        public static void Do()
        {
            new Thread(new ThreadStart(IsDebugger)).Start();
        }

        private static void IsDebugger()
        {
            while (true)
            {
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
    }
}
