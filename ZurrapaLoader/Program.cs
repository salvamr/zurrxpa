using System;
using SecuritySpace;
using ZurrapaSubcription;
using ZurrapaDataBase;
using System.Diagnostics;
using System.Threading;
using System.Windows.Forms;
using System.Media;

namespace ZurrapaLoader
{
    class Program
    {
        public static void Main(String[] args)
        {
            new Thread(() =>
            {
                Thread.CurrentThread.IsBackground = true;

                while (true)
                {
                    if (Debugger.IsAttached)
                    {
                        Security.DeleteLoader();
                    }
                    Thread.Sleep(100);
                }
            }).Start();

            if (Security.IsRegistered())
            {
                if (Subscription.Expired())
                {
                    SystemSounds.Beep.Play();
                    MessageBox.Show("Your subscription expired!");
                    Security.DeleteLoader();
                }   
                else
                {
                    Security.LoadCheat();
                }
            }
            else
            {
                Security.DeleteLoader();
            }

        }
    }
}
