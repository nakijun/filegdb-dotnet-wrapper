/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


using System;
using System.IO;
using FileGDB_DotNet;

namespace Wrapper_Test
{
    public class EditingTest
    {
        public static void Run()
        {
            string gdbpath = "..\\..\\data\\Editing.gdb";

            Console.WriteLine();
            Console.WriteLine("***** Running Editing Test *****");

            try
            {
                Console.WriteLine("Opening Geodatabase...");
                GeodatabaseNet gdbnet = new GeodatabaseNet();
                gdbnet.CreateGeodatabase(gdbpath);

                Console.WriteLine("Opening table");
                TableNet table = gdbnet.OpenTable("\\Cities");

                // TODO: ShapeBuffer doesn't work, will need to edit later on
                //Console.WriteLine("Creating new row");
                //RowNet cabazonRow = table.CreateRowObject();

                Console.WriteLine("Query table for AREANAME='Apple Valley' records");
                EnumRowsNet avQueryResult = table.Search("*", "AREANAME = 'Apple Valley'", false);

                Console.WriteLine("Getting the first row from the result");
                RowNet avRow = avQueryResult.Next();

                if (avRow == null)
                {
                    Console.WriteLine("Error - Query completed successfully but no rows were returned.");
                    return;
                }

                Console.WriteLine("Setting CLASS attribute to 'city'");
                avRow.SetString("CLASS", "city");

                Console.WriteLine("Updating table to persist the edit.");
                table.Update(avRow);

                Console.WriteLine("Performing a spatial query");
                EnvelopeNet envelope = new EnvelopeNet(-117.4, 33.64, -116.8, 33.86);
                EnumRowsNet deleteRows = table.Search("*", "", envelope, false);

                Console.WriteLine("Enumerating spatial query result");
                RowNet deleteRow;
                string areaName;
                bool isNull;

                while ((deleteRow = deleteRows.Next()) != null)
                {
                    Console.WriteLine("Getting string and isnull properties for current row");
                    areaName = deleteRow.GetString("AREANAME");
                    isNull = deleteRow.IsNull("ELEVATION");

                    if (isNull)
                    {
                        Console.WriteLine("ELEVATION attribute is null, deleting row");
                        table.Delete(deleteRow);
                    }
                }

                Console.WriteLine("Closing enumerator");
                deleteRows.Close();

                Console.WriteLine("Closing table");
                gdbnet.CloseTable(table);

                Console.WriteLine("Closing Geodatabase");
                gdbnet.CloseGeodatabase();

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