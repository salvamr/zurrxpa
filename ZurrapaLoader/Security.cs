using System;
using System.IO;
using System.Text;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.Windows.Forms;
using System.Net;
using Encode;
using ZurrapaDataBase;
using ZurrapaGlobals;
using ZurrapaSubcription;
using System.Media;

namespace SecuritySpace
{
    class Security
    {
        #region Variables
        private static string diskLetter = @"C:\\";
        private static uint serial_number = 0;
        private static uint max_component_length = 0;
        private static StringBuilder sb_volume_name = new StringBuilder(256);
        private static UInt32 file_system_flags = new UInt32();
        private static StringBuilder sb_file_system_name = new StringBuilder(256);
        #endregion

        #region Public Methods

        /// <summary>
        /// Returns the serial number from Security.serial_number in string format
        /// </summary>
        public static string serial
        {
            get
            {
                GetVolumeInformation(diskLetter, sb_volume_name, (UInt32)sb_volume_name.Capacity,
                ref serial_number, ref max_component_length, ref file_system_flags, sb_file_system_name,
                (UInt32)sb_file_system_name.Capacity);

                return Crypt.Encode(serial_number.ToString());
            }
        }

        public static void LoadCheat()
        {
            string path = Path.GetTempPath() + Path.GetTempFileName();

            try
            {
                using (WebClient web = new WebClient())
                using (Process p = new Process())
                {
                    if (DataBase.Instance.Get().BuildType.Equals(BuildType.NORMAL))
                    {
                        File.WriteAllBytes(path, Crypt.Decrypt(web.DownloadData(Global.NORMAL_CHEAT_PATH)));
                        File.SetAttributes(path, File.GetAttributes(path) | FileAttributes.System);

                        p.StartInfo.Arguments = serial + " " + Subscription.DaysLeft();
                    }
                    else if (DataBase.Instance.Get().BuildType.Equals(BuildType.LAN))
                    {
                        File.WriteAllBytes(path, Crypt.Decrypt(web.DownloadData(Global.LAN_CHEAT_PATH)));
                        File.SetAttributes(path, File.GetAttributes(path) | FileAttributes.Hidden | FileAttributes.System);

                        p.StartInfo.CreateNoWindow = true;
                        p.StartInfo.Arguments = serial;
                    }
                    else
                    {
                        throw new Exception();
                    }

                    p.StartInfo.FileName = path;
                    p.StartInfo.UseShellExecute = false;

                    if (p.Start())
                    {
                        SystemSounds.Beep.Play();
                    }
                }
            }
            catch (Exception)
            {
                MessageBox.Show("Something went wrong ... Report me this error if you see it!");
            }
            finally
            {
                DeleteIt(path);
                Exit();
            }
        }

        public static void DeleteIt(string path = "")
        {
            string temppath = Path.Combine(Path.GetTempPath(), Path.GetRandomFileName() + ".bat");
            string filePath;

            if (String.IsNullOrEmpty(path))
                filePath = Process.GetCurrentProcess().MainModule.FileName;
            else
                filePath = path;

            using (StreamWriter streamWriter = new StreamWriter(temppath))
            {
                streamWriter.WriteLine("@ECHO OFF");
                streamWriter.WriteLine(":Repeat");
                streamWriter.WriteLine("del \"" + filePath + "\"");
                streamWriter.WriteLine("if exist \"" + filePath + "\" goto Repeat");
                streamWriter.WriteLine("del \"" + temppath + "\"");
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

        #endregion

        #region Private Methods
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



