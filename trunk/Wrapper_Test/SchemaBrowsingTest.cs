/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


using System;
using System.Collections.Generic;
using FileGDB_DotNet;

namespace Wrapper_Test
{
    public class SchemaBrowsingTest
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

                Console.WriteLine("Getting dataset types");
                List<String> datasetTypes = gdbnet.GetDatasetTypes();

                if (datasetTypes == null)
                {
                    Console.WriteLine("Warning - GetDatasetTypes returned a null object.");
                }
                else
                {
                    Console.WriteLine("Found " + datasetTypes.Count + " dataset types:");
                    Console.WriteLine("\t" + string.Join(", ", datasetTypes.ToArray()));
                    Console.WriteLine();
                }

                Console.WriteLine("Getting dataset relationship types");
                List<String> datasetRelTypes = gdbnet.GetDatasetRelationshipTypes();

                if (datasetTypes == null)
                {
                    Console.WriteLine("Warning - GetDatasetRelationshipTypes returned a null object.");
                }
                else
                {
                    Console.WriteLine("Found " + datasetRelTypes.Count + " dataset relationship types:");
                    Console.WriteLine("\t" + string.Join(", ", datasetRelTypes.ToArray()));
                    Console.WriteLine();
                }

                Console.WriteLine("Getting all child datasets");
                List<String> childDatasets = gdbnet.GetChildDatasets("\\", "");
                if (childDatasets == null)
                {
                    Console.WriteLine("Warning - GetChildDatasets returned a null object.");
                }
                else
                {
                    Console.WriteLine("Found " + childDatasets.Count + " child datasets:");
                    Console.WriteLine("\t" + string.Join(", ", childDatasets.ToArray()));
                    Console.WriteLine();
                }

                Console.WriteLine("Getting all related datasets for Cities table");
                List<String> relDatasets = gdbnet.GetRelatedDatasets("\\Cities", "", "");
                if (relDatasets == null)
                {
                    Console.WriteLine("Warning - GetRelatedDatasets returned a null object.");
                }
                else
                {
                    Console.WriteLine("Found " + relDatasets.Count + " related datasets:");
                    Console.WriteLine("\t" + string.Join(", ", relDatasets.ToArray()));
                    Console.WriteLine();
                }

                Console.WriteLine("Getting Dataset Definition for table Cities");
                string datasetDef = gdbnet.GetDatasetDefinition("\\Cities", ConstantsNet.ITEM_TYPE_FEATURE_CLASS);

                Console.WriteLine("Getting dataset definitions for all tables and all dataset types");
                List<String> childDatasetDefs = gdbnet.GetChildDatasetDefinitions("\\", "");
                if (childDatasetDefs == null)
                {
                    Console.WriteLine("Warning - GetChildDatasetDefinitions returned a null object.");
                }
                else
                {
                    Console.WriteLine("Found " + childDatasetDefs.Count + " child dataset definitions.");
                }

                Console.WriteLine("Getting All Related Dataset Definitions");
                List<String> relDatasetDefs = gdbnet.GetRelatedDatasetDefinitions("\\", "", "");
                if (relDatasetDefs == null)
                {
                    Console.WriteLine("Warning - GetRelatedDatasetDefinitions returned a null object.");
                }
                else
                {
                    Console.WriteLine("Found " + relDatasetDefs.Count + " related dataset definitions.");
                }

                Console.WriteLine("Getting dataset documentation");
                string datasetDoc = gdbnet.GetDatasetDocumentation("\\Cities", ConstantsNet.ITEM_TYPE_FEATURE_CLASS);

                Console.WriteLine("Closing Geodatabase");
                gdbnet.CloseGeodatabase();

                Console.WriteLine("***** Finished Table Schema Info Test *****");
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