using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using SecuritySpace;
using System.Net;

namespace ZurrapaLoader
{
    class Program
    {
        [DllImport("test.dll")]
        public static extern void Zurrapa(string arg);
        /*Hacer una clase para leer las settings y una variable que almacene el hwid del server y usarlo
         dentro del Security.Do() para no usar un argumento*/
        public static void Main(String[] args)
        {
            Security.Do();

            try
            {
                Zurrapa(Security.serial);
            }
            catch (Exception e)
            {
                Console.WriteLine("Error: 404");
            }
        }
    }
}
