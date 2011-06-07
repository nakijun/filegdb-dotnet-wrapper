/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


using System;
using System.IO;
using FileGDB_DotNet;

namespace Wrapper_Test
{
    public class FeatureDatasetTest
    {
        public static void Run()
        {
            string gdbpath = "data\\fdsdemo.gdb";
            string transitpath = "data\\TransitFD.xml";
            string busstopspath = "data\\BusStopsTable.xml";

            Console.WriteLine();
            Console.WriteLine("***** Running Feature Dataset Test *****");

            try
            {
                GeodatabaseNet gdbnet = new GeodatabaseNet();

                if (Directory.Exists(gdbpath))
                {
                    Console.WriteLine("Geodatabase already exists, attempting to delete.");
                    gdbnet.DeleteGeodatabase(gdbpath);
                }

                Console.WriteLine("Creating geodatabase.");
                gdbnet.CreateGeodatabase(gdbpath);

                Console.WriteLine("Reading Dataset Definition");
                string featureDatasetDef;
                using (StreamReader sr = new StreamReader(transitpath))
                    featureDatasetDef = sr.ReadToEnd();

                Console.WriteLine("Creating feature dataset");
                gdbnet.CreateFeatureDataset(featureDatasetDef);

                string tableDef;
                using (StreamReader sr = new StreamReader(busstopspath))
                    tableDef = sr.ReadToEnd();

                Console.WriteLine("Creating table with Transit dataset as parent");
                TableNet table = gdbnet.CreateTable(tableDef, "\\Transit");

                Console.WriteLine("Closing Transit table");
                gdbnet.CloseTable(table);

                Console.WriteLine("Closing Geodatabase");
                gdbnet.CloseGeodatabase();

                Console.WriteLine("***** Finished Running Feature Dataset Test *****");
            }
            catch (FGDBException exc)
            {
                Console.WriteLine("Exception caught while running test.");
                Console.WriteLine("Code: " + exc.ErrorCode);
                Console.WriteLine("Message: " + exc);
                Console.WriteLine("Description: " + exc.ErrorDescription);
            }
        }
    }
}