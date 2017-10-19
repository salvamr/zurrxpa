using System;
using ZurrapaDataBase;
using ZurrapaGlobals;

namespace ZurrapaSubcription
{
    class Subcription
    {
        private static string ExpirationDate = DataBase.Instance.Get().ExpirationDate;

        public static bool Expired()
        {
            if (ExpirationDate.Equals("Never"))
                return false;

            return DaysLeft() < 0 ? true : false;
        }

        public static int DaysLeft()
        {
            if (ExpirationDate.Equals("Never"))
                return 1337;

            DateTime.TryParse(ExpirationDate, out DateTime expDate);

            TimeSpan dif = expDate - DateTime.Today;
            return dif.Days;
        }
    }
}
