using System;
using System.Diagnostics;

class Program
{
    static void Main()
    {
        Process process = new Process();
        process.StartInfo.FileName = "whoami";
        process.StartInfo.UseShellExecute = false;

        bool started = process.Start();

        if (started)
        {
            process.WaitForExit();
            Console.WriteLine("\nProcess ID is: " + Process.GetCurrentProcess().Id);
        }
        else
        {
            Console.WriteLine("Failed to start process.");
        }
    }
}
