using System;
using SecuritySpace;
using ZurrapaSubcription;
using ZurrapaDataBase;

namespace ZurrapaLoader
{
    class Program
    {
        public static void Main(String[] args)
        {
            Console.WriteLine(Security.IsRegistered());
            Console.ReadLine();

            if (Subcription.Expired())
                Security.DeleteLoader();

            Security.LoadCheat();
        }
    }
}
