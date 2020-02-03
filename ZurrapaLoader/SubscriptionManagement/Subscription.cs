using System;
using ZurrapaDataBase;
using ZurrapaGlobals;

namespace ZurrapaSubcription
{
    class Subscription
    {
        private static DataBaseStructure db = DataBase.Instance.Get();

        public static bool Expired()
        {
            if (db.ExpirationDate.Equals("Never"))
                return false;

            return DaysLeft() < 0 ? true : false;
        }

        public static int DaysLeft()
        {
            if (db.ExpirationDate.Equals("Never"))
                return 1337;

            DateTime.TryParse(db.ExpirationDate, out DateTime expDate);

            TimeSpan dif = expDate - DateTime.Today;
            return dif.Days;
        }

        public static bool IsRegistered()
        {
            try
            {
                if (String.IsNullOrEmpty(db.Name) || String.IsNullOrWhiteSpace(db.Name))
                    return false;

                return true;
            }
            catch (Exception)
            {
                return false;
            }

        }
    }
}
