using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Wolfram.NETLink;

namespace MathMain
{
    /// <summary>
    /// Program class.
    /// </summary>
    class Program
    {
        /// <summary>
        /// Main
        /// </summary>
        /// <param name="args"></param>
        static void Main(string[] args)
        {
            // This launches the Mathematica kernel:
            IKernelLink ml = null;

            try
            {
                // wolfram kernel.
                string[] mlArgs = { "-linkmode", "launch", "-linkname", @"C:\Program Files\Wolfram Research\Wolfram Engine\13.0\wolfram.exe" };

                // This launches the Mathematica kernel:
                ml = MathLinkFactory.CreateKernelLink(mlArgs);
            }
            catch (MathLinkException ex)
            {
                Console.WriteLine("Fatal error opening link: " + ex.Message);
                return;
            }

            try
            {
                // Discard the initial InputNamePacket the kernel will send when launched.
                ml.WaitAndDiscardAnswer();

                // The easiest way. Send the computation as a string and get the result in a single call:
                string result = ml.EvaluateToOutputForm(args[0], 0);
                Console.WriteLine(result);
            }
            catch (MathLinkException ex)
            {
                Console.WriteLine("MathLinkException occurred: " + ex.Message);
            }
            finally
            {
                ml.Close();
            }
        }
    }
}
