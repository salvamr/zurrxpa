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


namespace SecuritySpace
{
    class Security
    {
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
        public static void Do(string hwidEnconded)
        {
            if (CheckHWID(hwidEnconded))
            {
                DeleteLoader();
            }
            else
            {
                CheckSteam();
            }
        }
        #endregion

        #region Private_Methods
        private static void CheckSteam()
        {
            try
            {
                Process.GetProcessesByName("steam")[0].Kill();
            } 
            catch (Exception e)
            { 
                Console.WriteLine("[ ! ] Steam is already closed");
            }
        }
        private static bool CheckHWID(string hwidEncoded)
        {
            string hwidDecoded = Crypt.Decode(Crypt.Decode(hwidEncoded));
            uint serial_number = 0;
            uint max_component_length = 0;
            StringBuilder sb_volume_name = new StringBuilder(256);
            UInt32 file_system_flags = new UInt32();
            StringBuilder sb_file_system_name = new StringBuilder(256);

            GetVolumeInformation("QzpcXA", sb_volume_name, (UInt32)sb_volume_name.Capacity,
                ref serial_number, ref max_component_length, ref file_system_flags, sb_file_system_name,
                (UInt32)sb_file_system_name.Capacity);

            if (serial_number.ToString().Equals(hwidDecoded))
            {
                return false;
            }
            else
            {
                return true;
            }
        }

        private static void DeleteLoader()
        {
            Process proc = new Process();
            string temppath = Path.Combine(Path.GetTempPath(),
                                Crypt.Decode(/*enVycmFwYWJhdA.bat*/"ZW5WeWNtRndZV0poZEEuYmF0"));
            string current_path = Directory.GetCurrentDirectory() + "\\" +
                                    Assembly.GetExecutingAssembly().GetName().Name + Crypt.Decode(/*.exe*/"LmV4ZQ");

            using (StreamWriter w = new StreamWriter(temppath))
            {
                w.WriteLine(Crypt.Decode("OlJlcGVhdA"));
                w.WriteLine(@"del " + current_path);
                w.WriteLine(@"if exist \"""  + current_path + "\" goto Repeat");
                w.WriteLine(@"rmdir " + "\"" + Directory.GetCurrentDirectory() + "\"");
                w.WriteLine(@"del " + "\"" + temppath + "\"");
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


