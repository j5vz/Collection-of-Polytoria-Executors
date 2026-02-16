// hi this is v2 also yes i added linux and macos support

using System;
using System.IO;
using System.Linq;
using System.Diagnostics;
using System.Runtime.InteropServices;

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
            // ily colored terminal lines
            
            if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
            {
                WinShift();
            }
            else if (RuntimeInformation.IsOSPlatform(OSPlatform.Linux))
            {
                UnixShift("/etc/machine-id");
            }
            else if (RuntimeInformation.IsOSPlatform(OSPlatform.OSX))
            {
                MacShift();
            }

            Console.WriteLine("\nPress any key to exit this window...");
            Console.ReadKey();
        }

        static void WinShift()
        {
            try
            {
                string g = Guid.NewGuid().ToString();
                var crypto = Microsoft.Win32.Registry.LocalMachine.OpenSubKey(@"SOFTWARE\Microsoft\Cryptography", true);
                crypto?.SetValue("MachineGuid", g);

                var hw = Microsoft.Win32.Registry.LocalMachine.OpenSubKey(@"SYSTEM\CurrentControlSet\Control\IDConfigDB\Hardware Profiles\0001", true);
                hw?.SetValue("HwProfileGuid", "{" + g + "}");

                var nt = Microsoft.Win32.Registry.LocalMachine.OpenSubKey(@"SOFTWARE\Microsoft\Windows NT\CurrentVersion", true);
                nt?.SetValue("ProductId", $"{Entropy(5)}-{Entropy(5)}-{Entropy(5)}-{Entropy(5)}");

                Console.ForegroundColor = ConsoleColor.Green;
                Console.WriteLine("[+] Windows Registry ID(s) randomized.");
            }
            catch
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine("[!] Run monox.cs as Administrator.");
            }
        }

        static void UnixShift(string path)
        {
            try
            {
                string id = Entropy(32, true);
                File.WriteAllText(path, id);
                Console.ForegroundColor = ConsoleColor.Green;
                Console.WriteLine("[+] System HWID updated.");
            }
            catch
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine("[!] Sudo permissions are required to run monox.");
            }
        }

        static void MacShift()
        {
            try
            {
                string m = $"00:e0:4c:{Entropy(2, true)}:{Entropy(2, true)}:{Entropy(2, true)}";
                var proc = new ProcessStartInfo("sudo", $"ifconfig en0 ether {m}") { CreateNoWindow = true };
                Process.Start(proc)?.WaitForExit();
                Console.ForegroundColor = ConsoleColor.Green;
                Console.WriteLine($"[+] MacOS MAC set to {m}");
            }
            catch
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine("[!] Mac HWID change failed.");
            }
        }

        static string Entropy(int len, bool hex = false)
        {
            string p = hex ? "abcdef0123456789" : "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*";
            var r = new Random();
            return new string(Enumerable.Repeat(p, len).Select(s => s[r.Next(s.Length)]).ToArray());
        }
    }
}
