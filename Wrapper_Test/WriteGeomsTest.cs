/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


using System;
using System.IO;
using FileGDB_DotNet;

namespace Wrapper_Test
{
    public class WriteGeomsTest
    {
        public static void Run()
        {
            string gdbpath = "..\\data\\Geometries.gdb";

            Console.WriteLine();
            Console.WriteLine("***** Running Write Geometries Test *****");

            try
            {
                Console.WriteLine("Opening Geodatabase...");
                GeodatabaseNet gdbnet = new GeodatabaseNet();
                gdbnet.OpenGeodatabase(gdbpath);

                EditPoints(gdbnet);
                EditPolylines(gdbnet);

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

        private static void EditPoints(GeodatabaseNet gdbnet)
        {
            Console.WriteLine("Opening Cities table");
            TableNet table = gdbnet.OpenTable("\\Cities");

            Console.WriteLine("Executing table search for city 'Adelanto'.");
            EnumRowsNet queryRows = table.Search("*", "AREANAME='Adelanto'", false);
            RowNet row = queryRows.Next();

            if (row == null)
            {
                Console.WriteLine("No city found with name 'Adelanto'");
            }
            else
            {
                ShapeBufferNet shpBuffer = row.GetGeometry();
                PointNet pt = (PointNet)shpBuffer.GetGeometry();
                Console.WriteLine("City Found, Geometry details:");
                Console.WriteLine(String.Format("X: {0}  Y: {1}", pt.X, pt.Y));

                Console.WriteLine();
                pt.X += 10;
                pt.Y += 5;
                Console.WriteLine(String.Format("Offsetting X by 10 degrees, Y by 5 degrees.  New X/Y should be: {0}, {1}", pt.X, pt.Y));

                Console.WriteLine("Updating geometry in shape buffer");
                shpBuffer.SetGeometry(pt);
                row.SetGeometry(shpBuffer);

                Console.WriteLine("Updating row in table");
                table.Update(row);
            }
                
            Console.WriteLine("Closing enumerator.");
            queryRows.Close();

            Console.WriteLine("Re-querying table to get updated value");
            EnumRowsNet updatedRows = table.Search("*", "AREANAME='Adelanto'", false);
            RowNet updatedRow = updatedRows.Next();

            if (updatedRow == null)
            {
                Console.WriteLine("No city found with name 'Adelanto'");
            }
            else
            {
                ShapeBufferNet shpBuffer = updatedRow.GetGeometry();
                PointNet pt = (PointNet)shpBuffer.GetGeometry();
                Console.WriteLine(String.Format("Updated Geometry Details: X: {0}  Y: {1}", pt.X, pt.Y));
            }

            Console.WriteLine("Closing enumerator.");
            updatedRows.Close();

            Console.WriteLine("Closing Cities Table");
            gdbnet.CloseTable(table);
        }

        private static void EditPolylines(GeodatabaseNet gdbnet)
        {
            Console.WriteLine("Opening Street table");
            TableNet table = gdbnet.OpenTable("\\Street");

            Console.WriteLine("Executing table search for street 1.");
            EnumRowsNet queryRows = table.Search("*", "OBJECTID=1", false);
            RowNet row = queryRows.Next();

            if (row == null)
            {
                Console.WriteLine("No street found with OBJECTID 1");
            }
            else
            {
                ShapeBufferNet shpBuffer = row.GetGeometry();
                PolylineNet pl = (PolylineNet)shpBuffer.GetGeometry();
                Console.WriteLine("Street Found, Geometry details:");
                Console.WriteLine(String.Format("Number of parts: {0}  Number of points: {1}", pl.NumParts, pl.NumPoints));

                Console.WriteLine();
                PointNet pt1 = pl.Parts[0][0];
                Console.WriteLine(String.Format("First point coordinates: {0}, {1}", pt1.X, pt1.Y));

                Console.WriteLine("Offsetting first point X by 10, Y by 5.");
                pl.Parts[0][0].X += 10;
                pl.Parts[0][0].Y += 5;

                Console.WriteLine("Updating geometry in shape buffer");
                shpBuffer.SetGeometry(pl);
                row.SetGeometry(shpBuffer);

                Console.WriteLine("Updating row in table");
                table.Update(row);
            }

            Console.WriteLine("Closing enumerator.");
            queryRows.Close();

            Console.WriteLine("Re-querying table to get updated value");
            EnumRowsNet updatedRows = table.Search("*", "OBJECTID=1", false);
            RowNet updatedRow = updatedRows.Next();

            if (updatedRow == null)
            {
                Console.WriteLine("No street found with OBJECTID 1");
            }
            else
            {
                ShapeBufferNet shpBuffer = updatedRow.GetGeometry();
                PolylineNet pl = (PolylineNet)shpBuffer.GetGeometry();
                Console.WriteLine("Street Found, Geometry details:");
                Console.WriteLine(String.Format("Number of parts: {0}  Number of points: {1}", pl.NumParts, pl.NumPoints));

                PointNet pt1 = pl.Parts[0][0];
                Console.WriteLine(String.Format("First point coordinates: {0}, {1}", pt1.X, pt1.Y));
            }

            Console.WriteLine("Closing enumerator.");
            updatedRows.Close();

            // Create a new polyline
            Console.WriteLine("Creating a new RowNet object");
            RowNet newPlineRow = table.CreateRowObject();

            Console.WriteLine("Setting field values");
            newPlineRow.SetString("ROUTEID", "6407");
            newPlineRow.SetString("SEGMENTID", "SID766");
            newPlineRow.SetString("FACILITYID", "6407-SID766");
            newPlineRow.SetShort("ENABLED", 1);
            newPlineRow.SetString("NAME", "S INDIAN RIVER DR");
            newPlineRow.SetDouble("RECLENGTH", 10000.0);
            newPlineRow.SetShort("OWNEDBY", 1);
            newPlineRow.SetShort("MAINTBY", 1);
            newPlineRow.SetDate("LASTUPDATE", DateTime.Now);
            newPlineRow.SetString("LASTEDITOR", "CityWorks\\SasaI");

            Console.WriteLine("Creating a new polyline");
            PolylineNet newPoly = new PolylineNet();
            newPoly.Parts = new PointNet[1][];
            newPoly.Parts[0] = new PointNet[4];
            newPoly.Parts[0][0] = new PointNet(874562.707, 1143028.843);
            newPoly.Parts[0][1] = new PointNet(881192.573, 1124947.388);
            newPoly.Parts[0][2] = new PointNet(859463.106, 1125042.554);
            newPoly.Parts[0][3] = new PointNet(859559.993, 1143377.783);
            newPoly.Extent = new EnvelopeNet(859463.106, 881192.573, 1124947.388, 1143377.783);

            Console.WriteLine("Creating a new shapebuffer");
            ShapeBufferNet newShpBuffer = new ShapeBufferNet();
            Console.WriteLine("Assigning polyline geometry to shapebuffer");
            newShpBuffer.SetGeometry(newPoly);
            Console.WriteLine("Assigning shapebuffer to row");
            newPlineRow.SetGeometry(newShpBuffer);

            Console.WriteLine("Inserting row into table.");
            table.Insert(newPlineRow);

            Console.WriteLine("Closing Street Table");
            gdbnet.CloseTable(table);
        }
    }
}