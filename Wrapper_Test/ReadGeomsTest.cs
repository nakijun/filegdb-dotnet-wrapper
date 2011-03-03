/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


using System;
using FileGDB_DotNet;

namespace Wrapper_Test
{
    public class ReadGeomsTest
    {
        public static void Run()
        {
            string gdbpath = "..\\..\\data\\Geometries.gdb";

            Console.WriteLine();
            Console.WriteLine("***** Running Read Geometries Test *****");

            try
            {
                Console.WriteLine("Opening Geodatabase...");
                GeodatabaseNet gdbnet = new GeodatabaseNet();
                gdbnet.OpenGeodatabase(gdbpath);

                Console.WriteLine("Opening Cities table");
                TableNet table = gdbnet.OpenTable("\\Cities");

                Console.WriteLine("Executing table search.");
                EnumRowsNet queryRows = table.Search("*", "", true);

                RowNet row;
                ShapeBufferNet shpBuffer;

                Console.WriteLine("Enumerating point results (first 10 results only)...");
                int i = 0;
                PointNet point;
                while ((row = queryRows.Next()) != null && i++ < 10)
                {
                    shpBuffer = row.GetGeometry();
                    point = (PointNet) shpBuffer.GetGeometry();

                    Console.WriteLine(String.Format("X: {0}  Y: {1}", point.x, point.y));
                }

                Console.WriteLine("Closing enumerator.");
                queryRows.Close();

                Console.WriteLine("Closing Cities Table");
                gdbnet.CloseTable(table);

                /////////////////////////////

                Console.WriteLine("Opening Street table.");
                table = gdbnet.OpenTable("\\Street");

                Console.WriteLine("Executing table search.");
                queryRows = table.Search("*", "", true);

                Console.WriteLine("Enumerating polyline results (first 10 results only)...");
                i = 0;
                PolylineNet line;
                while ((row = queryRows.Next()) != null && i++ < 10)
                {
                    shpBuffer = row.GetGeometry();
                    line = (PolylineNet) shpBuffer.GetGeometry();

                    Console.WriteLine(String.Format("Polyline extent: {0}, {1}, {2}, {3}", line.Extent.xMin, line.Extent.yMin, line.Extent.xMax, line.Extent.yMax));
                    Console.WriteLine(String.Format("Number of Parts: {0}  Number of Points: {1}", line.NumParts, line.NumPoints));
                }

                Console.WriteLine("Closing enumerator.");
                queryRows.Close();

                Console.WriteLine("Closing Street Table");
                gdbnet.CloseTable(table);

                /////////////////////////////

                Console.WriteLine("Opening Admin2000 table.");
                table = gdbnet.OpenTable("\\Admin2000");

                Console.WriteLine("Executing table search.");
                queryRows = table.Search("*", "", true);

                Console.WriteLine("Enumerating polygon results (first 10 results only)...");
                i = 0;
                PolygonNet pgon;
                while ((row = queryRows.Next()) != null && i++ < 10)
                {
                    shpBuffer = row.GetGeometry();
                    pgon = (PolygonNet) shpBuffer.GetGeometry();

                    Console.WriteLine(String.Format("Polygon extent: {0}, {1}, {2}, {3}", pgon.Extent.xMin, pgon.Extent.yMin, pgon.Extent.xMax, pgon.Extent.yMax));
                    Console.WriteLine(String.Format("Number of Paths: {0}  Number of Points: {1}", pgon.NumPaths, pgon.NumPoints));
                }

                Console.WriteLine("Closing enumerator.");
                queryRows.Close();

                Console.WriteLine("Closing Admin2000 Table");
                gdbnet.CloseTable(table);


                Console.WriteLine("Closing geodatabase");
                gdbnet.CloseGeodatabase();

                Console.WriteLine("***** Finished Running Read Geometries Test *****");
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