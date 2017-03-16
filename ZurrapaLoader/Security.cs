using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using Microsoft.VisualBasic;
using System.Diagnostics;
using System.Reflection;
using Encode;
using System.Net;

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
        #endregion

        #region Public_Methods
        public static void Do()
        {
            if (CheckHWID())
            {
                DeleteLoader();
            }
            else
            {
                CheckSteam();
            }
        }
        #endregion
        
        public static string serial
        {
            get
            {
                return serial_number.ToString();
            }
        }

        #region Private_Methods
        private static void CheckSteam()
        {
            try
            {
                Process.GetProcessesByName("steam")[0].Kill();
            } 
            catch (Exception)
            { 
                Console.WriteLine("[ ! ] Steam is already closed");
            }
        }

        private static void CheckUSB()
        {

        }

        private static bool CheckHWID()
        {
            string subs;
            string line;

            GetVolumeInformation(Crypt.Decode("QzpcXA"), sb_volume_name, (UInt32)sb_volume_name.Capacity,
                ref serial_number, ref max_component_length, ref file_system_flags, sb_file_system_name,
                (UInt32)sb_file_system_name.Capacity);

            subs = new WebClient().DownloadString(Crypt.Decode("aHR0cDovL3p1cnJhcGEuaG9zdC9zdWJz"));

            using (StringReader reader = new StringReader(subs))
            {
                while ((line = reader.ReadLine()) != null)
                {
                    if(!line.StartsWith("/") && Crypt.Decode(line).Equals(serial_number.ToString()))
                    {
                        return false;
                    }
                }
            }
            return true;
        }

        private static void DeleteLoader()
        {
            Process proc = new Process();
            string temppath, current_path;

            temppath        = Path.Combine(Path.GetTempPath(), Crypt.Decode(/*enVycmFwYWJhdA.bat*/"ZW5WeWNtRndZV0poZEEuYmF0"));
            current_path    = Path.Combine(Directory.GetCurrentDirectory(), Assembly.GetExecutingAssembly().GetName().Name + Crypt.Decode(/*.exe*/"LmV4ZQ"));

            using (StreamWriter w = new StreamWriter(temppath))
            {
                w.WriteLine(":Repeat");
                w.WriteLine("del \"" + current_path + "\"");
                w.WriteLine("if exist \"" + current_path + "\" goto Repeat");
                w.WriteLine("rmdir \"" + Directory.GetCurrentDirectory() + "\"");
                w.WriteLine("del \"" + temppath + "\"");
                w.Close();
            }
            
            proc.StartInfo.CreateNoWindow = true;
            proc.StartInfo.WindowStyle = ProcessWindowStyle.Hidden;
            proc.StartInfo.FileName = temppath;
            proc.Start();
            Environment.Exit(0);
        }
        #endregion
    }
}


