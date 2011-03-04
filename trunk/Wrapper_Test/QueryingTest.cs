/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


using System;
using System.IO;
using FileGDB_DotNet;

namespace Wrapper_Test
{
    public class QueryingTest
    {
        public static void Run()
        {
            string gdbpath = "..\\..\\data\\Querying.gdb";

            Console.WriteLine();
            Console.WriteLine("***** Running Query Test *****");

            try
            {
                Console.WriteLine("Opening Geodatabase...");
                GeodatabaseNet gdbnet = new GeodatabaseNet();
                gdbnet.OpenGeodatabase(gdbpath);

                Console.WriteLine("Opening Cities table");
                TableNet table = gdbnet.OpenTable("\\Cities");

                Console.WriteLine("Executing table search.");
                EnumRowsNet attrQueryRows = table.Search("Shape, NAME, Pop1996", "TERM = 'City'", true);

                RowNet attrQueryRow;
                string cityName;
                long cityPop;

                Console.WriteLine("Enumerating query results...");
                while ((attrQueryRow = attrQueryRows.Next()) != null)
                {
                    cityName = attrQueryRow.GetString("NAME");
                    cityPop = attrQueryRow.GetInteger("Pop1996");

                    Console.WriteLine("City Name: " + cityName + "\tPopulation: " + cityPop);
                }

                Console.WriteLine("Closing enumerator.");
                attrQueryRows.Close();

                Console.WriteLine("Performing a spatial query.");
                EnvelopeNet envelope = new EnvelopeNet(-66.0, -64.0, 46.0, 48.0);
                EnumRowsNet spQueryRows = table.Search("NAME", "", envelope, true);

                Console.WriteLine("Enumerating spatial query results.");
                RowNet spQueryRow;
                while ((spQueryRow = spQueryRows.Next()) != null)
                {
                    cityName = spQueryRow.GetString("NAME");
                    Console.WriteLine("City Name: " + cityName);
                }

                Console.WriteLine("Closing spatial query enumerator");
                spQueryRows.Close();

                Console.WriteLine("Closing Table");
                gdbnet.CloseTable(table);

                Console.WriteLine("Closing geodatabase");
                gdbnet.CloseGeodatabase();

                Console.WriteLine("***** Finished Running Query Test *****");
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