/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


using System;
using System.IO;
using FileGDB_DotNet;

namespace Wrapper_Test
{
    public class TableSchemaInfoTest
    {
        public static void Run()
        {
            string gdbpath = "..\\data\\ExecuteSQL.gdb";

            Console.WriteLine();
            Console.WriteLine("***** Running Table Schema Info Test *****");

            try
            {
                GeodatabaseNet gdbnet = new GeodatabaseNet();

                Console.WriteLine("Opening database");
                gdbnet.OpenGeodatabase(gdbpath);

                Console.WriteLine("Opening table");
                TableNet table = gdbnet.OpenTable("\\Cities");

                Console.WriteLine("Getting Table Definition");
                string tableDef = table.GetDefinition();

                Console.WriteLine("Getting table docutmentation");
                string tableDoc = table.GetDocumentation();

                Console.WriteLine("Setting table documentation");
                table.SetDocumentation(tableDoc);

                Console.WriteLine("Closing table");
                gdbnet.CloseTable(table);

                Console.WriteLine("Closing Geodatabase");
                gdbnet.CloseGeodatabase();

                Console.WriteLine("***** Finished Table Schema Info Test *****");
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