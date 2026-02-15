using System;
using Microsoft.Win32;
using System.Linq;

namespace Monoxide
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Title = "Monoxide";
            
            Console.ForegroundColor = ConsoleColor.Cyan;
            Console.WriteLine("[ MONOXIDE ]");
            Console.WriteLine("Monoxide HWID Spoofer by @j5vz");
            Console.WriteLine("Polytoria devs suck ass LOLOLOLOL");
            Console.ResetColor();

            string newHwId = "{" + Guid.NewGuid().ToString() + "}";
            string newMac = GenerateEntropy(12);

            bool success = ApplyIdentity(newHwId, newMac);

            if (success)
            {
                Console.ForegroundColor = ConsoleColor.Green;
                Console.WriteLine("[+] HWID changed successfully.");
            }
            else
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine("[!] Failed to write registry keys. Run monox Administrator.");
            }

            Console.WriteLine("\nPress any key to exit...");
            Console.ReadKey();
        }

        static bool ApplyIdentity(string guid, string mac)
        {
            try
            {
                var cryptography = Registry.LocalMachine.OpenSubKey(@"SOFTWARE\Microsoft\Cryptography", true);
                cryptography?.SetValue("MachineGuid", Guid.NewGuid().ToString());

                var hwProfile = Registry.LocalMachine.OpenSubKey(@"SYSTEM\CurrentControlSet\Control\IDConfigDB\Hardware Profiles\0001", true);
                hwProfile?.SetValue("HwProfileGuid", guid);

                var winNt = Registry.LocalMachine.OpenSubKey(@"SOFTWARE\Microsoft\Windows NT\CurrentVersion", true);
                winNt?.SetValue("ProductId", $"{GenerateEntropy(5)}-{GenerateEntropy(5)}-{GenerateEntropy(5)}-{GenerateEntropy(5)}");

                return true;
            }
            catch
            {
                return false;
            }
        }

        static string GenerateEntropy(int len)
        {
            const string pool = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+-=[]{}|";
            var rnd = new Random();
            return new string(Enumerable.Repeat(pool, len).Select(s => s[rnd.Next(s.Length)]).ToArray());
        }
    }
}
