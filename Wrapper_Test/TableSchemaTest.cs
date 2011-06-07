/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


using System;
using System.IO;
using FileGDB_DotNet;

namespace Wrapper_Test
{
    public class TableSchemaTest
    {
        private const string DOMAIN_DEFINITION =
            "<esri:Domain xsi:type='esri:RangeDomain' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xmlns:xs='http://www.w3.org/2001/XMLSchema' xmlns:esri='http://www.esri.com/schemas/ArcGIS/10.1'>" +
            "<DomainName>LaneDomain</DomainName>" +
            "<FieldType>esriFieldTypeSmallInteger</FieldType>" +
            "<MergePolicy>esriMPTDefaultValue</MergePolicy>" +
            "<SplitPolicy>esriSPTDefaultValue</SplitPolicy>" +
            "<Description>The number of lanes on a road</Description>" +
            "<Owner></Owner>" +
            "<MaxValue xsi:type='xs:short'>12</MaxValue>" +
            "<MinValue xsi:type='xs:short'>1</MinValue>" +
            "</esri:Domain>";

        private const string STREET_TYPE_FIELD =
            "<esri:Field xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xmlns:xs='http://www.w3.org/2001/XMLSchema' xmlns:esri='http://www.esri.com/schemas/ArcGIS/10.1' xsi:type='esri:Field'>" +
            "<Name>night</Name>" +
            "<Type>esriFieldTypeString</Type>" +
            "<IsNullable>true</IsNullable>" +
            "<Length>4</Length>" +
            "<Precision>0</Precision>" +
            "<Scale>0</Scale>" +
            "<AliasName>day</AliasName>" +
            "<ModelName>night</ModelName>" +
            "<DefaultValue xsi:type=\"xs:string\">afternoon</DefaultValue>" +
            "</esri:Field>";

        private const string STREET_TYPE_INDEX =
            "<esri:Index xsi:type='esri:Index' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xmlns:xs='http://www.w3.org/2001/XMLSchema' xmlns:esri='http://www.esri.com/schemas/ArcGIS/10.1'>" +
            "<Name>StreetTypeIdx</Name>" +
            "<IsUnique>false</IsUnique>" +
            "<IsAscending>true</IsAscending>" +
            "<Fields xsi:type='esri:Fields'>" +
            "<FieldArray xsi:type='esri:ArrayOfField'>" +
            "<Field xsi:type='esri:Field'>" +
            "<Name>StreetType</Name>" +
            "<Type>esriFieldTypeSmallInteger</Type>" +
            "<IsNullable>false</IsNullable>" +
            "<Length>2</Length>" +
            "<Precision>0</Precision>" +
            "<Scale>0</Scale>" +
            "<Required>true</Required>" +
            "<Editable>false</Editable>" +
            "<DomainFixed>true</DomainFixed>" +
            "<AliasName>StreetType</AliasName>" +
            "<ModelName>StreetType</ModelName>" +
            "</Field>" +
            "</FieldArray>" +
            "</Fields>" +
            "</esri:Index>";

        private const string SUBTYPE_DEFINITION =
            "<esri:Subtype xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xs=\"http://www.w3.org/2001/XMLSchema\" xmlns:esri=\"http://www.esri.com/schemas/ArcGIS/10.1\" xsi:type=\"esri:Subtype\">" +
            "<SubtypeName>subtype three</SubtypeName>" +
            "<SubtypeCode>99</SubtypeCode>" +
            "<FieldInfos xsi:type='esri:ArrayOfSubtypeFieldInfo'>" +
            "<SubtypeFieldInfo xsi:type='esri:SubtypeFieldInfo'>" +
            "<FieldName>percentComplete</FieldName>" +
            "<DomainName>LaneDomain</DomainName>" +
            "<DefaultValue xsi:type='xs:double'>56</DefaultValue>" +
            "</SubtypeFieldInfo>" +
            "</FieldInfos>" +
            "</esri:Subtype>";

        private const string SUBTYPE_DEFINITION_ALTERED =
            "<esri:Subtype xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xs=\"http://www.w3.org/2001/XMLSchema\" xmlns:esri=\"http://www.esri.com/schemas/ArcGIS/10.1\" xsi:type=\"esri:Subtype\">" +
            "<SubtypeName>subtype three</SubtypeName>" +
            "<SubtypeCode>98</SubtypeCode>" +
            "<FieldInfos xsi:type='esri:ArrayOfSubtypeFieldInfo'>" +
            "<SubtypeFieldInfo xsi:type='esri:SubtypeFieldInfo'>" +
            "<FieldName>percentComplete</FieldName>" +
            "<DomainName>LaneDomain</DomainName>" +
            "<DefaultValue xsi:type='xs:double'>56</DefaultValue>" +
            "</SubtypeFieldInfo>" +
            "</FieldInfos>" +
            "</esri:Subtype>";


        public static void Run()
        {
            string gdbpath = "data\\tableschematest.gdb";
            string fcdefpath = "data\\Table.xml";

            Console.WriteLine();
            Console.WriteLine("***** Running Table Schema Test *****");

            try
            {
                GeodatabaseNet gdbnet = new GeodatabaseNet();

                if (Directory.Exists(gdbpath))
                {
                    Console.WriteLine("Geodatabase already exists, attempting to delete.");
                    gdbnet.DeleteGeodatabase(gdbpath);
                }

                Console.WriteLine("Creating Geodatabase...");
                gdbnet.CreateGeodatabase(gdbpath);

                if (!Directory.Exists(gdbpath))
                {
                    Console.WriteLine("ERROR - Geodatabase creation reported no errors but no geodatabase found.  Exiting...");
                    return;
                }

                Console.WriteLine("Creating a domain definition.");
                gdbnet.CreateDomain(DOMAIN_DEFINITION);


                Console.WriteLine("Reading XML Feature Class Definition");
                string tableDef;
                using (StreamReader sr = new StreamReader(fcdefpath))
                    tableDef = sr.ReadToEnd();

                Console.WriteLine("Creating Feature Class");
                // Create the table with no parent
                TableNet streetsTable = gdbnet.CreateTable(tableDef, "");

                Console.WriteLine("Adding StreetType field");
                streetsTable.AddField(STREET_TYPE_FIELD);

                Console.WriteLine("Deleting Width field");
                streetsTable.DeleteField("Width");

                Console.WriteLine("Creating StreetTypeIndex");
                streetsTable.AddIndex(STREET_TYPE_INDEX);

                Console.WriteLine("Creating a new subtype");
                streetsTable.EnableSubtypes("StreetType", SUBTYPE_DEFINITION);

                Console.WriteLine("Getting the default subtype code");
                int defaultCode = streetsTable.GetDefaultSubtypeCode();
                Console.WriteLine("The default subtype code is: " + defaultCode);

                Console.WriteLine("Setting the default subtype code to 87");
                defaultCode = 87;
                streetsTable.SetDefaultSubtypeCode(defaultCode);

                Console.WriteLine("Getting the default subtype code again");
                defaultCode = streetsTable.GetDefaultSubtypeCode();
                Console.WriteLine("The new default subtype code is: " + defaultCode);

                Console.WriteLine("Altering subtype definition");
                streetsTable.AlterSubtype(SUBTYPE_DEFINITION_ALTERED);

                Console.WriteLine("Deleting Local Streets subtype");
                streetsTable.DeleteSubtype("Local Streets");

                Console.WriteLine("Closing table");
                gdbnet.CloseTable(streetsTable);

                Console.WriteLine("Closing geodatabase");
                gdbnet.CloseGeodatabase();

                Console.WriteLine("***** Finished Running Table Schema Test *****");
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