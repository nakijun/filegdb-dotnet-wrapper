/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


using System;
using System.IO;
using FileGDB_DotNet;

namespace Wrapper_Test
{
    public class SQLTest
    {
        public static void Run()
        {
            string gdbpath = "..\\data\\ExecuteSQL.gdb";

            Console.WriteLine();
            Console.WriteLine("***** Running SQL Test *****");

            try
            {
                GeodatabaseNet gdbnet = new GeodatabaseNet();

                Console.WriteLine("Opening geodatabase.");
                gdbnet.OpenGeodatabase(gdbpath);

                string sqlStatement = "SELECT NAME, Pop1996 FROM Cities WHERE TERM = 'City'";
                EnumRowsNet attrQueryRows = gdbnet.ExecuteSQL(sqlStatement, true);

                RowNet attrQueryRow;
                string cityName;
                long cityPop;

                Console.WriteLine("Enumerating sql query results...");
                while ((attrQueryRow = attrQueryRows.Next()) != null)
                {
                    cityName = attrQueryRow.GetString("NAME");
                    cityPop = attrQueryRow.GetInteger("Pop1996");

                    Console.WriteLine("City Name: " + cityName + "\tPopulation: " + cityPop);
                }

                Console.WriteLine("Closing sql query result enumerator");
                attrQueryRows.Close();

                Console.WriteLine("Closing geodatabase");
                gdbnet.CloseGeodatabase();

                Console.WriteLine("Finished running SQL Test");

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