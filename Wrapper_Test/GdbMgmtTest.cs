/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


using System;
using System.IO;
using FileGDB_DotNet;

namespace Wrapper_Test
{
    public class GdbMgmtTest
    {
        public static void Run()
        {
            string gdbpath = "..\\data\\gdbmgmttest.gdb";

            Console.WriteLine();
            Console.WriteLine("***** Running Geodatabase Management Test *****");

            try
            {
                Console.WriteLine("Creating Geodatabase...");
                GeodatabaseNet gdbnet = new GeodatabaseNet();
                gdbnet.CreateGeodatabase(gdbpath);

                if (!Directory.Exists(gdbpath))
                {
                    Console.WriteLine("ERROR - Geodatabase creation reported no errors but no geodatabase found.  Exiting...");
                    return;
                }

                Console.WriteLine("Closing Geodatabase");
                gdbnet.CloseGeodatabase();

                Console.WriteLine("Opening/Closing Geodatabase");
                gdbnet.OpenGeodatabase(gdbpath);
                gdbnet.CloseGeodatabase();

                Console.WriteLine("Deleting Geodatabase");
                gdbnet.DeleteGeodatabase(gdbpath);

                Console.WriteLine("***** Finished Running Geodatabase Management Test *****");   
            }
            catch (FGDBException exc)
            {
                Console.WriteLine("Exception caught while running test.");
                Console.WriteLine("Code: " + exc.ErrorCode);
                Console.WriteLine("Message: " + exc);
            }
        }
    }
}