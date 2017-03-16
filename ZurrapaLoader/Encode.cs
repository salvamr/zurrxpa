using System;
using System.Text;
using System.Text.RegularExpressions;

namespace Encode
{
    class Crypt
    {
        private static bool hayError;
        /// <summary>
        /// Decode a passed string
        /// </summary>
        /// <param name="encodedData"></param>
        /// <returns></returns>
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
