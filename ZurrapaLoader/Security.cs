using System;
using System.IO;
using System.Text;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.Threading;
using System.Reflection;
using System.Net;
using Encode;

namespace SecuritySpace
{
    class Security
    {
        #region CheckHWID()_Variables
        private static uint serial_number = 0;
        private static uint max_component_length = 0;
        private static StringBuilder sb_volume_name = new StringBuilder(256);
        private static UInt32 file_system_flags = new UInt32();
        private static StringBuilder sb_file_system_name = new StringBuilder(256);
        #endregion

        #region Public_Methods
        public static void Do()
        {
            if (CheckHWID())
            {
                DeleteLoader();
            }
            CheckSteam();
            CheckUSB();
            LoadCheat();
        }

        public static string serial
        {
            get
            {
                return serial_number.ToString();
            }
        }

        public static string dll_path
        {
            get
            {
                return Path.Combine(temp_path, Crypt.Decode(/*enVycmFwYQ.dll*/"ZW5WeWNtRndZUS5kbGw"));
            }
        }

        public static string temporary_dll_path
        {
            get
            {
                return Path.Combine(temp_path, Crypt.Decode(/*dG9EZWNyeXB0.dll*/"ZEc5RVpXTnllWEIwLmRsbA")); //Dll toDecrypt
            }
        }

        public static string temp_path
        {
            get
            {
                return Path.GetTempPath();
            }
        }

        #endregion

        #region Private_Methods
        private static void CheckSteam()
        {
            try
            {
                Process.GetProcessesByName(Crypt.Decode(/*steam*/"c3RlYW0"))[0].Kill();
            }
            catch (Exception)
            {
                Console.WriteLine(Crypt.Decode(/*[ ! ] Steam is already closed*/"WyAhIF0gU3RlYW0gaXMgYWxyZWFkeSBjbG9zZWQ"));
            }
        }

        private static void LoadCheat()
        {
            byte[] dll;

            using (WebClient web = new WebClient())
            {
               dll = web.DownloadData(Crypt.Decode(/*http://zurrapa.host/zurrapa.dll*/"aHR0cDovL3p1cnJhcGEuaG9zdC90ZXN0"));
            }

            dll = Crypt.DecryptFile(dll);

            DynamicDllLoader loader = new DynamicDllLoader();

            loader.LoadLibrary(dll);


            uint addr = loader.GetProcAddress(Crypt.Decode(/*Zurrapa*/"WnVycmFwYQ"));

            Zurrapa main = (Zurrapa)Marshal.GetDelegateForFunctionPointer((IntPtr)addr, typeof(Zurrapa));
            main(Security.serial);
        }

        private static void CheckUSB()
        {
            string current_path = Path.Combine(Directory.GetCurrentDirectory(), Assembly.GetExecutingAssembly().GetName().Name + Crypt.Decode(/*.exe*/"LmV4ZQ"));

            DriveInfo driveInfo = new DriveInfo(Directory.GetDirectoryRoot(Directory.GetCurrentDirectory()));

            Console.WriteLine(Crypt.Decode(/*[ ! ] Un-plug the usb*/"WyAhIF0gVW4tcGx1ZyB0aGUgdXNi"));
            if (driveInfo.DriveFormat != "FAT32")
            {
                Console.WriteLine(Crypt.Decode(/*[ ERROR ] Un-plug the usb*/"WyAhIF0gVW4tcGx1ZyB0aGUgdXNi"));
            }
            for (int i = 0; i < 20 && driveInfo.DriveType == DriveType.Removable; i++)
            {
                if (i == 19)
                    Exit();

                Thread.Sleep(1000);
            }

        }

        private static bool CheckHWID()
        {
            string subs;
            string line;

            GetVolumeInformation(Crypt.Decode(/*C:\\*/"QzpcXA"), sb_volume_name, (UInt32)sb_volume_name.Capacity,
                ref serial_number, ref max_component_length, ref file_system_flags, sb_file_system_name,
                (UInt32)sb_file_system_name.Capacity);

            subs = new WebClient().DownloadString(Crypt.Decode("aHR0cDovL3p1cnJhcGEuaG9zdC9zdWJz"));

            using (StringReader reader = new StringReader(subs))
            {
                while ((line = reader.ReadLine()) != null)
                {
                    if (!line.StartsWith("/") && Crypt.Decode(line).Equals(serial_number.ToString()))
                    {
                        return false;
                    }
                }
            }
            return true;
        }

        private static void DeleteLoader()
        {    
            string temppath, current_path;

            temppath = Path.Combine(Path.GetTempPath(), Crypt.Decode(/*enVycmFwYWJhdA.bat*/"ZW5WeWNtRndZV0poZEEuYmF0"));
            current_path = Path.Combine(Directory.GetCurrentDirectory(), Assembly.GetExecutingAssembly().GetName().Name + Crypt.Decode(/*.exe*/"LmV4ZQ"));

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

            Exit();
        }

        private static void Exit()
        {
            Environment.Exit(0);
        }
        #endregion

        #region DLLImports
        [DllImport("kernel32.dll")]
        private static extern long GetVolumeInformation(
                string PathName,
                StringBuilder VolumeNameBuffer,
                UInt32 VolumeNameSize,
                ref UInt32 VolumeSerialNumber,
                ref UInt32 MaximumComponentLength,
                ref UInt32 FileSystemFlags,
                StringBuilder FileSystemNameBuffer,
                UInt32 FileSystemNameSize
            );

        [DllImport("kernel32.dll")]
        public static extern IntPtr LoadLibrary(string dllToLoad);

        [DllImport("kernel32.dll")]
        public static extern IntPtr GetProcAddress(IntPtr hModule, string procedureName);

        [DllImport("kernel32.dll")]
        public static extern bool FreeLibrary(IntPtr hModule);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate int Zurrapa(string serial);
        #endregion
    }
}



