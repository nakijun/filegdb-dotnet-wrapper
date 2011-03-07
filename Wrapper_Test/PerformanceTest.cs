/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


using System;
using System.IO;
using FileGDB_DotNet;

namespace Wrapper_Test
{
    public class PerformanceTest
    {
        static Random rand = new Random();
        public static void Run()
        {
            string gdbpath = "..\\..\\data\\Performance.gdb";

            Console.WriteLine();
            Console.WriteLine("***** Running PerformanceTest *****");

            try
            {
                Console.WriteLine("Opening Geodatabase...");
                GeodatabaseNet gdbnet = new GeodatabaseNet();
                gdbnet.OpenGeodatabase(gdbpath);

                //TestPoints(gdbnet);

                //TestMultiPoints(gdbnet);
                
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
            return min + rand.NextDouble()*(max - min);
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

            TestPoints(gdbnet, 100000);

            Console.WriteLine("Finished running point performance test.");
        }

        private static void TestPoints(GeodatabaseNet gdbnet, int numPoints)
        {
            Console.WriteLine("Writing " + numPoints + " points to the database.");
            TableNet table = gdbnet.OpenTable("\\Points");

            DateTime start = DateTime.Now;
            
            RowNet row;
            ShapeBufferNet sb;
            PointNet pt;
            for (int i = 0; i < numPoints; i++)
            {
                row = table.CreateRowObject();
                row.SetString("TextField", "Random text string.");
                row.SetDouble("DoubleField1", RandomDouble());
                row.SetDouble("DoubleField2", RandomDouble());
                row.SetDate("DateField", DateTime.Now);
                row.SetInteger("IntegerField1", RandomInteger());
                row.SetInteger("IntegerField2", RandomInteger());

                double x = RandomDouble(-360, 360);
                double y = RandomDouble(-180, 180);
                
                pt = new PointNet(x, y);
                sb = new ShapeBufferNet();
                sb.SetGeometry(pt);
                row.SetGeometry(sb);

                table.Insert(row);
            }

            TimeSpan ts = DateTime.Now - start;
            Console.WriteLine("Wrote " + numPoints + " points to the database in " + ts.TotalMilliseconds.ToString("N") + "ms");


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

            gdbnet.CloseTable(table);
        }

        private static void TestMultiPoints(GeodatabaseNet gdbnet)
        {
            Console.WriteLine("Running multipoint performance test........");

            TestMultiPoints(gdbnet, 10000, 1000);

            Console.WriteLine("Finished running multipoint performance test.");
        }

        private static void TestMultiPoints(GeodatabaseNet gdbnet, int numMultiPoints, int maxPointsPerMP)
        {
            Console.WriteLine("Running multipoint performance test........");

            Console.WriteLine("Writing " + numMultiPoints + " multipoints to the database.");
            TableNet table = gdbnet.OpenTable("\\Multipoints");

            MultiPointNet mp;
            ShapeBufferNet sb;
            RowNet row;

            DateTime start = DateTime.Now;

            int totPoints = 0;
            for (int i = 0; i < numMultiPoints; i++)
            {
                // Generate 1-100 points per multipoint
                int numSubPoints = rand.Next(1, maxPointsPerMP);
                totPoints += numSubPoints;

                mp = new MultiPointNet { Points = new PointNet[numSubPoints] };

                for (int j = 0; j < numSubPoints; j++)
                    mp.Points[j] = new PointNet(RandomDouble(-360, 360), RandomDouble(-180, 180));

                mp.UpdateExtent();
                row = table.CreateRowObject();
                row.SetString("TextField", "Random text string.");
                row.SetDouble("DoubleField1", RandomDouble());
                row.SetDouble("DoubleField2", RandomDouble());
                row.SetDate("DateField", DateTime.Now);
                row.SetInteger("IntegerField1", RandomInteger());
                row.SetInteger("IntegerField2", RandomInteger());

                sb = new ShapeBufferNet();
                sb.SetGeometry(mp);
                row.SetGeometry(sb);
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

            gdbnet.CloseTable(table);
            Console.WriteLine("Finished running multipoint performance test.");
        }

        private static void TestPolylines(GeodatabaseNet gdbnet)
        {
            Console.WriteLine("Running polyline performance test........");

            TestPolylines(gdbnet, 1000, 5, 100);

            Console.WriteLine("Finished running polyline performance test.");
        }

        private static void TestPolylines(GeodatabaseNet gdbnet, int numPolylines, int numParts, int maxPointsPerPart)
        {
            if (numParts < 1)
                numParts = 1;
            if (maxPointsPerPart < 2)
                maxPointsPerPart = 2;

            Console.WriteLine("Running polyline performance test........");

            Console.WriteLine("Writing " + numPolylines + " to the database.");
            TableNet table = gdbnet.OpenTable("\\Lines");

            PolylineNet pl;
            ShapeBufferNet sb;
            RowNet row;

            DateTime start = DateTime.Now;
            int totPoints = 0;
            for (int i=0; i<numPolylines; i++)
            {
                pl = new PolylineNet();
                int parts = rand.Next(1, numParts);
                pl.Parts = new PointNet[parts][];
                for (int j=0; j<parts; j++)
                {
                    int points = rand.Next(2, maxPointsPerPart);
                    pl.Parts[j] = new PointNet[points];
                    for (int k=0; k<points; k++)
                    {
                        pl.Parts[j][k] = new PointNet(RandomDouble(-360, 360), RandomDouble(-180, 180));
                        totPoints++;
                    }
                }

                pl.UpdateExtent();
                row = table.CreateRowObject();
                row.SetString("TextField", "Random text string.");
                row.SetDouble("DoubleField1", RandomDouble());
                row.SetDouble("DoubleField2", RandomDouble());
                row.SetDate("DateField", DateTime.Now);
                row.SetInteger("IntegerField1", RandomInteger());
                row.SetInteger("IntegerField2", RandomInteger());

                sb = new ShapeBufferNet();
                sb.SetGeometry(pl);
                row.SetGeometry(sb);
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

            gdbnet.CloseTable(table);
            Console.WriteLine("Finished running polyline performance test.");
        }
    }
}