using System;
using System.IO;
using System.Text;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.Threading;
using System.Reflection;
using System.Windows.Forms;
using System.Net;
using Encode;

namespace SecuritySpace
{
    class Security
    {
        #region Variables
        private static uint serial_number = 0;
        private static uint max_component_length = 0;
        private static StringBuilder sb_volume_name = new StringBuilder(256);
        private static UInt32 file_system_flags = new UInt32();
        private static StringBuilder sb_file_system_name = new StringBuilder(256);
        #endregion

        #region Public_Methods
        #region Main_Method
        /// <summary>
        /// Main method from SecuritySpace
        /// </summary>
        public static void Do()
        {
            if (CheckHWID(@"C:\\"))
            {
                DeleteLoader();
            }
            CheckSteam();
            CheckUSB();
            LoadCheat(@"http://zurrapa.host/enVycmFwYU5vcm1hbA"); //"http://zurrapa.host/enVycmFwYU5vcm1hbA"
        }
        #endregion

        /// <summary>
        /// Returns the serial number from Security.serial_number in string format
        /// </summary>
        public static string serial
        {
            get
            {
                return Crypt.Encode(serial_number.ToString());
            }
        }
        #endregion

        #region Private_Methods

        private static void CheckSteam()
        {
            try
            {
                Process.GetProcessesByName("steam")[0].Kill();
                Console.WriteLine("[ + ] Steam has been closed");
            }
            catch (Exception)
            {
                Console.WriteLine("[ + ] Steam is already closed");
            }

            try
            {
                Process.GetProcessesByName("csgo")[0].Kill();
                Console.WriteLine("[ + ] CSGO has been closed");
            }
            catch (Exception)
            {
            }
        }

        private static void LoadCheat(string base64URL)
        {          
            try
            {
                using (WebClient web = new WebClient())
                {
                    DynamicDllLoader loader = new DynamicDllLoader();
                    loader.LoadLibrary(Crypt.Decrypt(web.DownloadData(base64URL)));

                    Zurrapa main = (Zurrapa)Marshal.GetDelegateForFunctionPointer((IntPtr)loader.GetProcAddress("Zurrapa"), typeof(Zurrapa));

                    main(serial);
                }
            }
            catch (Exception e)
            {
                MessageBox.Show(e.StackTrace, "Error");
            }
            finally
            {
                Exit();
            }
        }

        private static void CheckUSB()
        {
            DriveInfo driveInfo = new DriveInfo(Directory.GetDirectoryRoot(Directory.GetCurrentDirectory()));

            if (driveInfo.DriveType != DriveType.Removable)
            {
                MessageBox.Show("Execute me from an USB", "Error");
                Exit();
            }

            if (driveInfo.DriveFormat != "FAT32")
            {
                MessageBox.Show("Format your USB to FAT32", "Error");
                Exit();
            }
        }

        private static bool CheckHWID(string diskLetter)
        {
            string line;

            GetVolumeInformation(diskLetter, sb_volume_name, (UInt32)sb_volume_name.Capacity,
                ref serial_number, ref max_component_length, ref file_system_flags, sb_file_system_name,
                (UInt32)sb_file_system_name.Capacity);

            using (WebClient web = new WebClient())
            {
                using (StringReader reader = new StringReader(web.DownloadString("http://zurrapa.host/YzNWaWN3")))
                {
                    while ((line = reader.ReadLine()) != null)
                    {
                        if (!line.StartsWith("/") && Crypt.Decode(line).Equals(serial_number.ToString()))
                        {
                            return false;
                        }
                    }
                }
            }
            return true;
        }

        private static void DeleteLoader()
        {    
            string temppath, current_path;

            temppath = Path.Combine(Path.GetTempPath(), "enVycmFwYWJhdA.bat");
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
        private delegate int Zurrapa(string hwid);
        #endregion
    }
}



