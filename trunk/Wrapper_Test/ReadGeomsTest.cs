/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


using System;
using FileGDB_DotNet;

namespace Wrapper_Test
{
    public class 
        ReadGeomsTest
    {
        public static void Run()
        {
            string gdbpath = "..\\data\\Geometries.gdb";

            Console.WriteLine();
            Console.WriteLine("***** Running Read Geometries Test *****");

            try
            {
                Console.WriteLine("Opening Geodatabase...");
                GeodatabaseNet gdbnet = new GeodatabaseNet();
                gdbnet.OpenGeodatabase(gdbpath);

                ReadCities(gdbnet);
                ReadStreets(gdbnet);
                ReadAdmin2000(gdbnet);


                Console.WriteLine("Closing geodatabase");
                gdbnet.CloseGeodatabase();

                Console.WriteLine("***** Finished Running Read Geometries Test *****");
            }
            catch (FGDBException exc)
            {
                Console.WriteLine("Exception caught while running test.");
                Console.WriteLine("Code: " + exc.ErrorCode);
                Console.WriteLine("Message: " + exc);
                Console.WriteLine("Description: " + exc.ErrorDescription);
            }
        }

        private static void ReadCities(GeodatabaseNet gdbnet)
        {
            Console.WriteLine("Opening Cities table");
            TableNet table = gdbnet.OpenTable("\\Cities");

            Console.WriteLine("Executing table search.");
            EnumRowsNet queryRows = table.Search("*", "", true);

            RowNet row;
            PointShapeBufferNet psb;

            Console.WriteLine("Enumerating point results (first 10 results only)...");
            int i = 0;
            PointNet[] pts;
            while ((row = queryRows.Next()) != null && i++ < 10)
            {
                psb = (PointShapeBufferNet)row.GetGeometry();
                psb.GetPoints(out pts);

                Console.WriteLine(String.Format("X: {0}  Y: {1}", pts[0].x, pts[0].y));
            }

            Console.WriteLine("Closing enumerator.");
            queryRows.Close();

            Console.WriteLine("Closing Cities Table");
            gdbnet.CloseTable(table);
        }

        private static void ReadStreets(GeodatabaseNet gdbnet)
        {
            Console.WriteLine("Opening Street table.");
            TableNet table = gdbnet.OpenTable("\\Street");

            Console.WriteLine("Executing table search.");
            EnumRowsNet queryRows = table.Search("*", "", true);

            Console.WriteLine("Enumerating polyline results (first 10 results only)...");
            int i = 0;
            RowNet row;
            MultiPartShapeBufferNet mpsb;
            PointNet[] pts;
            EnvelopeNet extent;

            while ((row = queryRows.Next()) != null && i++ < 10)
            {
                mpsb = (MultiPartShapeBufferNet)row.GetGeometry();
                mpsb.GetPoints(out pts);
                extent = mpsb.GetExtent();

                Console.WriteLine(String.Format("Polyline extent: {0}, {1}, {2}, {3}", extent.XMin, extent.YMin, extent.XMax, extent.YMax));
                Console.WriteLine(String.Format("Number of Parts: {0}  Number of Points: {1}", mpsb.GetNumParts(), mpsb.GetNumPoints()));
            }

            Console.WriteLine("Closing enumerator.");
            queryRows.Close();

            Console.WriteLine("Closing Street Table");
            gdbnet.CloseTable(table);
        }

        private static void ReadAdmin2000(GeodatabaseNet gdbnet)
        {
            Console.WriteLine("Opening Admin2000 table.");
            TableNet table = gdbnet.OpenTable("\\Admin2000");

            Console.WriteLine("Executing table search.");
            EnumRowsNet queryRows = table.Search("*", "", true);

            Console.WriteLine("Enumerating polygon results (first 10 results only)...");
            int i = 0;
            RowNet row;
            MultiPartShapeBufferNet mpsb;
            PointNet[] pts;
            EnvelopeNet extent;

            while ((row = queryRows.Next()) != null && i++ < 10)
            {
                mpsb = (MultiPartShapeBufferNet)row.GetGeometry();
                mpsb.GetPoints(out pts);
                extent = mpsb.GetExtent();

                Console.WriteLine(String.Format("Polygon extent: {0}, {1}, {2}, {3}", extent.XMin, extent.YMin, extent.XMax, extent.YMax));
                Console.WriteLine(String.Format("Number of Parts: {0}  Number of Points: {1}", mpsb.GetNumParts(), mpsb.GetNumPoints()));
            }

            Console.WriteLine("Closing enumerator.");
            queryRows.Close();

            Console.WriteLine("Closing Admin2000 Table");
            gdbnet.CloseTable(table);
        }
    }
}