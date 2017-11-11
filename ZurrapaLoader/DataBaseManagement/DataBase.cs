using FireSharp;
using FireSharp.Config;
using System;
using System.Net;
using ZurrapaGlobals;
using SecuritySpace;

namespace ZurrapaDataBase
{
    public class DataBase
    {
        private FirebaseConfig Config { get; set; }
        private FirebaseClient Client { get; set; }
        private DateTime ExpireDate { get; set; }

        #region Singleton
        private static DataBase _instance;

        public static DataBase Instance
        {
            get
            {
                if (_instance == null)
                {
                    _instance = new DataBase();
                }
                return _instance;
            }
        }

        private DataBase()
        {
            this.Config = new FirebaseConfig
            {
                AuthSecret = Global.AUTH_SECRET,
                BasePath = Global.BASEPATH
            };

            this.Client = new FirebaseClient(Config);

            if (DateTime.TryParse(Get().ExpirationDate, out DateTime temp))
                this.ExpireDate = temp;
        }
        #endregion

        public bool Set(DataBaseStructure dbStructure)
        {
            return this.Client.Set<DataBaseStructure>(Security.serial, dbStructure).StatusCode.Equals(HttpStatusCode.OK) ? true : false;
        }

        public DataBaseStructure Get()
        {
            return this.Client.Get(Security.serial).ResultAs<DataBaseStructure>(); 
        }
    }
}
