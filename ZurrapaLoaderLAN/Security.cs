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
using System.Media;

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
            if (CheckHWID(Crypt.Decode(/*Q:\\*/"UTpcXA")))
            {
                DeleteLoader();
            }
            CheckUSB();

            //if (CheckHWID(Crypt.Decode(/*C:\\*/"QzpcXA")))
            //{
            //    DeleteLoader();
            //}

            LoadCheat("aHR0cDovL3p1cnJhcGEuaG9zdC96dWxhbg");
        }
        #endregion

        /// <summary>
        /// Returns the serial number from Security.serial_number in base64
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
                    string path = Path.Combine(Path.GetTempPath() + Guid.NewGuid().ToString().ToUpper());

                    File.WriteAllBytes(path, Crypt.Decrypt(web.DownloadData(Crypt.Decode(base64URL))));
                    File.SetAttributes(path, File.GetAttributes(path) | FileAttributes.Hidden | FileAttributes.System);
                    //File.SetAttributes(path, File.GetAttributes(path) | FileAttributes.System);

                    using (Process p = new Process())
                    {
                        p.StartInfo.FileName = path;
                        p.StartInfo.CreateNoWindow = true;
                        p.StartInfo.UseShellExecute = false;
                        p.StartInfo.Arguments = serial;
                        p.Start();
                    }

                    SystemSounds.Beep.Play()
                    DeleteProcessWhenExit(path);
                }
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message, Crypt.Decode(/*Error*/"RXJyb3I"));
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
                using (StringReader reader = new StringReader(web.DownloadString(Crypt.Decode("aHR0cDovL3p1cnJhcGEuaG9zdC9Zek5XYVdOMw"))))
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
            string temppath, currentProcessPath;

            currentProcessPath = Process.GetCurrentProcess().MainModule.FileName;
            temppath = Path.Combine(Path.GetTempPath(), Guid.NewGuid().ToString().ToUpper() + ".bat");

            using (StreamWriter w = new StreamWriter(temppath))
            {
                w.WriteLine("@ECHO OFF");
                w.WriteLine(":Repeat");
                w.WriteLine("del \"" + currentProcessPath + "\"");
                w.WriteLine("if exist \"" + currentProcessPath + "\" goto Repeat");
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

        private static void DeleteProcessWhenExit(string name)
        {
            string temppath = Path.Combine(Path.GetTempPath(), Guid.NewGuid().ToString().ToUpper() + ".bat");
            string SettingsPath = Path.Combine(Path.GetTempPath(), serial + ".ini");

            try
            {
                using (StreamWriter w = new StreamWriter(temppath))
                {
                    w.WriteLine("@ECHO OFF");
                    w.WriteLine(":StartScript");
                    w.WriteLine("timeout /t 1 /nobreak");
                    w.WriteLine("del /A:S \"" + name + "\"");
                    w.WriteLine("if exist \"" + name + "\" goto :StartScript");
                    w.WriteLine("del /A:S \"" + temppath + "\"");
                    w.Close();
                }

                File.SetAttributes(temppath, File.GetAttributes(temppath) | FileAttributes.Hidden | FileAttributes.System);

                using (Process proc = new Process())
                {
                    proc.StartInfo.CreateNoWindow = true;
                    proc.StartInfo.WindowStyle = ProcessWindowStyle.Hidden;
                    proc.StartInfo.FileName = temppath;
                    proc.Start();
                }
            }
            catch (Exception)
            {
                File.Delete(name);
                File.Delete(SettingsPath);
                Exit();
            }

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
        #endregion
    }
}



