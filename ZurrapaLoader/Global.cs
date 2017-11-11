using System.Configuration;

namespace ZurrapaGlobals
{
    public enum BuildType
    {
        NORMAL,
        LAN
    }

    public class Global
    {
        public static string AUTH_SECRET = ConfigurationManager.AppSettings["authSecret"];
        public static string BASEPATH = ConfigurationManager.AppSettings["basePathFireBase"];
        public static string NORMAL_CHEAT_PATH = ConfigurationManager.AppSettings["normalCheatURL"];
        public static string LAN_CHEAT_PATH = ConfigurationManager.AppSettings["lanCheatURL"];
    }
}
