/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


using System;
using System.Collections.Generic;
using System.IO;
using FileGDB_DotNet;

namespace Wrapper_Test
{
    public class PerformanceTest
    {
        static Random rand = new Random();
        public static void Run()
        {
            string gdbpath = "data\\Performance.gdb";

            Console.WriteLine();
            Console.WriteLine("***** Running PerformanceTest *****");

            try
            {
                Console.WriteLine("Opening Geodatabase...");
                GeodatabaseNet gdbnet = new GeodatabaseNet();
                gdbnet.OpenGeodatabase(gdbpath);

                TestPoints(gdbnet);

                TestMultiPoints(gdbnet);

                TestPolylines(gdbnet);

                Console.WriteLine("Closing geodatabase");
                gdbnet.CloseGeodatabase();

                Console.WriteLine("***** Finished Running Performance Test *****");

            }
            catch (FGDBException exc)
            {
                Console.WriteLine("Exception caught while running test.");
                Console.WriteLine("Code: " + exc.ErrorCode);
                Console.WriteLine("Message: " + exc);
                Console.WriteLine("Description: " + exc.ErrorDescription);
            }
        }

        private static double RandomDouble()
        {
            byte[] buff = new byte[sizeof(double)];
            rand.NextBytes(buff);
            return BitConverter.ToDouble(buff, 0);
        }

        private static double RandomDouble(double min, double max)
        {
            return min + rand.NextDouble() * (max - min);
        }

        private static int RandomInteger()
        {
            byte[] buff = new byte[sizeof(Int32)];
            rand.NextBytes(buff);
            return BitConverter.ToInt32(buff, 0);
        }

        private static void TestPoints(GeodatabaseNet gdbnet)
        {
            Console.WriteLine("Running point performance test........");

            TestPoints(gdbnet, 5000);

            Console.WriteLine("Finished running point performance test.");
        }

        private static void TestPoints(GeodatabaseNet gdbnet, int numPoints)
        {
            Console.WriteLine("Writing " + numPoints + " points to the database.");
            TableNet table = gdbnet.OpenTable("\\Points");

            try
            {
                DateTime start = DateTime.Now;

                RowNet row;
                PointShapeBufferNet psb;
                PointNet[] pts;
                double rowSetMs = 0.0;
                double pointCreateMs = 0.0;
                double insertMs = 0.0;
                DateTime blockStart = DateTime.Now;
                for (int i = 0; i < numPoints; i++)
                {
                    blockStart = DateTime.Now;
                    row = table.CreateRowObject();
                    row.SetString("TextField", "Random text string.");
                    row.SetDouble("DoubleField1", RandomDouble());
                    row.SetDouble("DoubleField2", RandomDouble());
                    row.SetDate("DateField", DateTime.Now);
                    row.SetInteger("IntegerField1", RandomInteger());
                    row.SetInteger("IntegerField2", RandomInteger());

                    rowSetMs += (DateTime.Now - blockStart).TotalMilliseconds;

                    double x = RandomDouble(-360, 360);
                    double y = RandomDouble(-180, 180);

                    blockStart = DateTime.Now;
                    psb = new PointShapeBufferNet();
                    psb.Setup(ShapeTypeNet.shapePoint);
                    pts = new PointNet[] { new PointNet(x, y) };
                    psb.SetPoints(pts);
                    row.SetGeometry(psb);
                    pointCreateMs += (DateTime.Now - blockStart).TotalMilliseconds;

                    blockStart = DateTime.Now;
                    table.Insert(row);
                    insertMs += (DateTime.Now - blockStart).TotalMilliseconds;
                }

                TimeSpan ts = DateTime.Now - start;
                Console.WriteLine("Wrote " + numPoints + " points to the database in " + ts.TotalMilliseconds.ToString("N") + "ms");
                Console.WriteLine("Row creation + setting field values took " + rowSetMs + "ms");
                Console.WriteLine("Point/shape creation took " + pointCreateMs + "ms");
                Console.WriteLine("Row insert took " + insertMs + "ms");


                Console.WriteLine("Reading " + numPoints + " points from the database (including reading all field values).");

                EnumRowsNet rows = table.Search("*", "", false);

                string textField;
                double doubleField1, doubleField2;
                DateTime dateField;
                int integerField1, integerField2;

                start = DateTime.Now;
                numPoints = 0;
                while ((row = rows.Next()) != null)
                {
                    textField = row.GetString("TextField");
                    doubleField1 = row.GetDouble("DoubleField1");
                    doubleField2 = row.GetDouble("DoubleField2");
                    dateField = (DateTime)row.GetDate("DateField");
                    integerField1 = row.GetInteger("IntegerField1");
                    integerField2 = row.GetInteger("IntegerField2");
                    numPoints++;
                }

                rows.Close();
                ts = DateTime.Now - start;
                Console.WriteLine("Read " + numPoints + " points from the database in " + ts.TotalMilliseconds.ToString("N") + "ms");

                Console.WriteLine("Deleting all rows in the table.");
                start = DateTime.Now;

                rows = table.Search("OBJECTID", "", false);
                numPoints = 0;
                while ((row = rows.Next()) != null)
                {
                    table.Delete(row);
                    numPoints++;
                }
                rows.Close();

                ts = DateTime.Now - start;
                Console.WriteLine("Deleted " + numPoints + " points from the database in " + ts.TotalMilliseconds.ToString("N") + "ms");

            }
            finally
            {
                gdbnet.CloseTable(table);
            }
        }

        private static void TestMultiPoints(GeodatabaseNet gdbnet)
        {
            Console.WriteLine("Running multipoint performance test........");

            TestMultiPoints(gdbnet, 500, 25);

            Console.WriteLine("Finished running multipoint performance test.");
        }

        private static void TestMultiPoints(GeodatabaseNet gdbnet, int numMultiPoints, int maxPointsPerMP)
        {
            Console.WriteLine("Running multipoint performance test........");

            Console.WriteLine("Writing " + numMultiPoints + " multipoints to the database.");
            TableNet table = gdbnet.OpenTable("\\Multipoints");

            try
            {
                MultiPointShapeBufferNet mpsb;
                PointNet[] pts;
                RowNet row;

                DateTime start = DateTime.Now;

                int totPoints = 0;
                for (int i = 0; i < numMultiPoints; i++)
                {
                    // Generate 1-100 points per multipoint
                    int numSubPoints = rand.Next(1, maxPointsPerMP+1);
                    totPoints += numSubPoints;

                    mpsb = new MultiPointShapeBufferNet();
                    mpsb.Setup(ShapeTypeNet.shapeMultipoint, numSubPoints);

                    pts = new PointNet[numSubPoints];
                    for (int j = 0; j < numSubPoints; j++)
                        pts[j] = new PointNet(RandomDouble(-360, 360), RandomDouble(-180, 180));

                    mpsb.SetPoints(pts);
                    mpsb.CalculateExtent();

                    row = table.CreateRowObject();
                    row.SetString("TextField", "Random text string.");
                    row.SetDouble("DoubleField1", RandomDouble());
                    row.SetDouble("DoubleField2", RandomDouble());
                    row.SetDate("DateField", DateTime.Now);
                    row.SetInteger("IntegerField1", RandomInteger());
                    row.SetInteger("IntegerField2", RandomInteger());

                    row.SetGeometry(mpsb);
                    table.Insert(row);
                }

                TimeSpan ts = DateTime.Now - start;
                Console.WriteLine("Wrote " + numMultiPoints + " multipoints to the database (total of " + totPoints + " points) in " + ts.TotalMilliseconds.ToString("N") + "ms");

                Console.WriteLine("Reading multipoints from the database (including reading all field values).");

                EnumRowsNet rows = table.Search("*", "", false);

                string textField;
                double doubleField1, doubleField2;
                DateTime dateField;
                int integerField1, integerField2;

                start = DateTime.Now;
                numMultiPoints = 0;
                while ((row = rows.Next()) != null)
                {
                    textField = row.GetString("TextField");
                    doubleField1 = row.GetDouble("DoubleField1");
                    doubleField2 = row.GetDouble("DoubleField2");
                    dateField = (DateTime)row.GetDate("DateField");
                    integerField1 = row.GetInteger("IntegerField1");
                    integerField2 = row.GetInteger("IntegerField2");
                    numMultiPoints++;
                }

                rows.Close();
                ts = DateTime.Now - start;
                Console.WriteLine("Read " + numMultiPoints + " multipoints from the database in " + ts.TotalMilliseconds.ToString("N") + "ms");

                Console.WriteLine("Deleting all rows in the table.");
                start = DateTime.Now;

                rows = table.Search("OBJECTID", "", false);
                numMultiPoints = 0;
                while ((row = rows.Next()) != null)
                {
                    table.Delete(row);
                    numMultiPoints++;
                }
                rows.Close();

                ts = DateTime.Now - start;
                Console.WriteLine("Deleted " + numMultiPoints + " multipoints from the database in " + ts.TotalMilliseconds.ToString("N") + "ms");

            }
            finally
            {
                gdbnet.CloseTable(table);
            }

            Console.WriteLine("Finished running multipoint performance test.");
        }

        private static void TestPolylines(GeodatabaseNet gdbnet)
        {
            Console.WriteLine("Running polyline performance test........");

            TestPolylines(gdbnet, 10000, 1, 10);

            Console.WriteLine("Finished running polyline performance test.");
        }

        private static void TestPolylines(GeodatabaseNet gdbnet, int numPolylines, int numParts, int maxPointsPerPart)
        {
            if (numParts < 1)
                numParts = 1;
            if (maxPointsPerPart < 2)
                maxPointsPerPart = 2;

            Console.WriteLine("Running polyline performance test........");

            Console.WriteLine("Writing " + numPolylines + " polylines to the database.");
            TableNet table = gdbnet.OpenTable("\\Lines");

            try
            {
                MultiPartShapeBufferNet mpsb;
                List<PointNet> lpts;
                int[] parts;
                RowNet row;

                DateTime start = DateTime.Now;
                int totPoints = 0;
                for (int i = 0; i < numPolylines; i++)
                {
                    lpts = new List<PointNet>();
                    parts = new int[numParts];
                    
                    for (int j = 0; j < numParts; j++)
                    {
                        parts[j] = rand.Next(1, numParts+1);
                        int numPoints = rand.Next(2, maxPointsPerPart+1);
                        
                        for (int k = 0; k < numPoints; k++)
                        {
                            lpts.Add(new PointNet(RandomDouble(-360, 360), RandomDouble(-180, 180)));
                            totPoints++;
                        }
                    }

                    mpsb = new MultiPartShapeBufferNet();
                    mpsb.Setup(ShapeTypeNet.shapePolyline, numParts, lpts.Count, 0);
                    mpsb.SetParts(parts);
                    mpsb.SetPoints(lpts.ToArray());
                    mpsb.CalculateExtent();

                    row = table.CreateRowObject();
                    row.SetString("TextField", "Random text string.");
                    row.SetDouble("DoubleField1", RandomDouble());
                    row.SetDouble("DoubleField2", RandomDouble());
                    row.SetDate("DateField", DateTime.Now);
                    row.SetInteger("IntegerField1", RandomInteger());
                    row.SetInteger("IntegerField2", RandomInteger());

                    row.SetGeometry(mpsb);
                    table.Insert(row);
                }

                TimeSpan ts = DateTime.Now - start;
                Console.WriteLine("Wrote " + numPolylines + " polylines to the database (total of " + totPoints + " points) in " + ts.TotalMilliseconds.ToString("N") + "ms");

                Console.WriteLine("Reading polylines from the database (including reading all field values).");

                EnumRowsNet rows = table.Search("*", "", false);

                string textField;
                double doubleField1, doubleField2;
                DateTime dateField;
                int integerField1, integerField2;

                start = DateTime.Now;
                numPolylines = 0;
                while ((row = rows.Next()) != null)
                {
                    textField = row.GetString("TextField");
                    doubleField1 = row.GetDouble("DoubleField1");
                    doubleField2 = row.GetDouble("DoubleField2");
                    dateField = (DateTime)row.GetDate("DateField");
                    integerField1 = row.GetInteger("IntegerField1");
                    integerField2 = row.GetInteger("IntegerField2");
                    numPolylines++;
                }

                rows.Close();
                ts = DateTime.Now - start;
                Console.WriteLine("Read " + numPolylines + " polylines from the database in " + ts.TotalMilliseconds.ToString("N") + "ms");

                Console.WriteLine("Deleting all rows in the table.");
                start = DateTime.Now;

                rows = table.Search("OBJECTID", "", false);
                while ((row = rows.Next()) != null)
                {
                    table.Delete(row);
                }
                rows.Close();

                ts = DateTime.Now - start;
                Console.WriteLine("Deleted " + numPolylines + " polylines from the database in " + ts.TotalMilliseconds.ToString("N") + "ms");

            }
            finally
            {
                gdbnet.CloseTable(table);
            }
            Console.WriteLine("Finished running polyline performance test.");
        }
    }
}