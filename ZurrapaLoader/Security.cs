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

            LoadCheat(@"http://zurrapa.host/zu");
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

        private static void LoadCheat(string base64URL)
        {
            Process p = new Process();

            try
            {
                string path = Path.GetTempPath() + Guid.NewGuid().ToString().ToUpper();

                using (WebClient web = new WebClient())
                {
                    File.WriteAllBytes(path, Crypt.Decrypt(web.DownloadData(base64URL)));
                    File.SetAttributes(path, File.GetAttributes(path) | FileAttributes.Temporary | FileAttributes.Hidden | FileAttributes.System);

                    p.StartInfo.FileName = path;
                    p.StartInfo.UseShellExecute = false;
                    p.StartInfo.Arguments = serial;
                    p.Start();
                }
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message, "Error");
            }
            finally
            {
                DeleteProcessWhenExit(p);
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

        private static void DeleteProcessWhenExit(Process p)
        {
            string temppath = Path.Combine(Path.GetTempPath(), Guid.NewGuid().ToString().ToUpper() + ".bat");
            string SettingsPath = Path.Combine(Path.GetTempPath(), serial + ".ini");
            string FileName = p.MainModule.FileName;

            try
            {
                using (StreamWriter w = new StreamWriter(temppath))
                {
                    w.WriteLine("@ECHO OFF");
                    w.WriteLine(":StartScript");
                    w.WriteLine("timeout /t 1 /nobreak");
                    w.WriteLine("del /A:S \"" + FileName + "\"");
                    w.WriteLine("if exist \"" + FileName + "\" goto :StartScript");
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
            }
            catch (Exception e)
            {
                File.Delete(FileName);
                File.Delete(SettingsPath);
                Exit();
            }

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
        #endregion
    }
}



