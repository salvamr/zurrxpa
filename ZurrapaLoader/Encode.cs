using System;
using System.Text;

namespace Encode
{
    class Crypt
    {
        private static bool hayError;
        public static string Decode(string encodedData)
        {
            do
            {
                hayError = false;
                try 
                {
                    return Encoding.UTF8.GetString(Convert.FromBase64String(encodedData));
                }
                catch (Exception)
                {
                    encodedData += "=";
                    hayError = true;
                }
            } while (hayError);

            return null;
        }
    }
}
