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
                Console.WriteLine("Description: " + exc.ErrorDescription);
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
                PointShapeBufferNet shpBuffer = (PointShapeBufferNet)row.GetGeometry();
                PointNet[] points;
                shpBuffer.GetPoints(out points);
                PointNet pt = points[0];

                Console.WriteLine("City Found, Geometry details:");
                Console.WriteLine(String.Format("X: {0}  Y: {1}", pt.x, pt.y));

                Console.WriteLine();
                pt.x += 10;
                pt.y += 5;
                Console.WriteLine(String.Format("Offsetting X by 10 degrees, Y by 5 degrees.  New X/Y should be: {0}, {1}", pt.x, pt.y));

                Console.WriteLine("Updating geometry in shape buffer");
                shpBuffer.SetPoints(points);
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
                PointShapeBufferNet shpBuffer = (PointShapeBufferNet)updatedRow.GetGeometry();
                PointNet[] points;
                shpBuffer.GetPoints(out points);
                PointNet pt = points[0];
                Console.WriteLine(String.Format("Updated Geometry Details: X: {0}  Y: {1}", pt.x, pt.y));
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
                MultiPartShapeBufferNet shpBuffer = (MultiPartShapeBufferNet)row.GetGeometry();
                Console.WriteLine("Street Found, Geometry details:");
                Console.WriteLine(String.Format("Number of parts: {0}  Number of points: {1}", shpBuffer.GetNumParts(), shpBuffer.GetNumPoints()));

                Console.WriteLine();
                PointNet[] points;
                shpBuffer.GetPoints(out points);
                PointNet pt1 = points[0];
                Console.WriteLine(String.Format("First point coordinates: {0}, {1}", pt1.x, pt1.y));

                Console.WriteLine("Offsetting first point X by 10, Y by 5.");
                pt1.x += 10;
                pt1.y += 5;

                Console.WriteLine("Updating geometry in shape buffer");
                shpBuffer.SetPoints(points);
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
                MultiPartShapeBufferNet shpBuffer = (MultiPartShapeBufferNet)updatedRow.GetGeometry();
                Console.WriteLine("Street Found, Geometry details:");
                Console.WriteLine(String.Format("Number of parts: {0}  Number of points: {1}", shpBuffer.GetNumParts(), shpBuffer.GetNumPoints()));

                PointNet[] points;
                shpBuffer.GetPoints(out points);
                PointNet pt1 = points[0];
                Console.WriteLine(String.Format("First point coordinates: {0}, {1}", pt1.x, pt1.y));
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

            Console.WriteLine("Creating a new shapebuffer");
            MultiPartShapeBufferNet newShpBuffer = new MultiPartShapeBufferNet();
            newShpBuffer.Setup(ShapeTypeNet.shapePolyline, 1, 4, 0);

            PointNet[] polyPoints = {
                new PointNet(874562.707, 1143028.843),
                new PointNet(881192.573, 1124947.388),
                new PointNet(859463.106, 1125042.554),
                new PointNet(859559.993, 1143377.783)
            };
            newShpBuffer.SetPoints(polyPoints);
            newShpBuffer.SetParts(new int[] { 0 });
            newShpBuffer.CalculateExtent();

            Console.WriteLine("Assigning shapebuffer to row");
            newPlineRow.SetGeometry(newShpBuffer);

            Console.WriteLine("Inserting row into table.");
            table.Insert(newPlineRow);

            Console.WriteLine("Closing Street Table");
            gdbnet.CloseTable(table);
        }
    }
}