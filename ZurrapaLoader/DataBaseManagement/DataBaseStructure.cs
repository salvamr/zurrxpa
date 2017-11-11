using System;
using ZurrapaGlobals;
using ZurrapaLoader.HardwareIDManagement;

namespace ZurrapaDataBase
{
    public class DataBaseStructure
    {
        public BuildType BuildType { get; set; }
        public String Name { get; set; }
        public String ExpirationDate { get; set; }
        public HardwareIDModel Hardware { get; set; }
    }
}
