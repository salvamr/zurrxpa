using System;
using SecuritySpace;
using ZurrapaSubcription;
using ZurrapaDataBase;
using System.Diagnostics;
using System.Threading;
using System.Windows.Forms;
using System.Media;
using ZurrapaLoader.HardwareIDManagement;

namespace ZurrapaLoader
{
    class Program
    {
        public static void Main(String[] args)
        {
            //new Thread(() =>
            //{
            //    Thread.CurrentThread.IsBackground = true;

            //    while (true)
            //    {
            //        if (Debugger.IsAttached)
            //        {
            //            Security.DeleteLoader();
            //        }
            //        Thread.Sleep(100);
            //    }
            //}).Start();

            Console.WriteLine(HardwareIDInfo.VolumeSerial());
            Console.ReadLine();
            if (Subscription.IsRegistered())
            {
                if (Subscription.Expired())
                {
                    SystemSounds.Beep.Play();
                    MessageBox.Show("Your subscription expired!");
                    Security.DeleteIt();
                }   
                else
                {
                    Security.LoadCheat();
                }
            }
            else
            {
                Security.DeleteIt();
            }

        }
    }
}
