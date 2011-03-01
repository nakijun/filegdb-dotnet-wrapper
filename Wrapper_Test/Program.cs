/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Wrapper_Test
{
    class Program
    {
        static void Main(string[] args)
        {
            WriteIntro();

            Console.Write("Test #> ");
            string input = Console.ReadLine();
            while (String.IsNullOrEmpty(input) || !input.Equals("exit", StringComparison.InvariantCultureIgnoreCase))
            {
                if (!String.IsNullOrEmpty(input))
                {
                    switch (input.ToLower())
                    {
                        case "1":
                            GdbMgmtTest.Run();
                            break;
                        case "2":
                            TableSchemaTest.Run();
                            break;
                        case "all":
                            RunAllTests();
                            break;
                    }
                }

                Console.Write("Test #> ");
                input = Console.ReadLine();
            }
        }

        private static void RunAllTests()
        {
            GdbMgmtTest.Run();
            TableSchemaTest.Run();
        }

        private static void WriteIntro()
        {
            Console.WriteLine("Enter a number for the test to run.  Type ALL to execute all tests, EXIT to finish.\n");
            Console.WriteLine("1: Geodatabase Management (Create/Open/Close/Delete)");
            Console.WriteLine("2: Table Schema (Create Table, Create/Alter/Delete Subtype");
        }
    }
}
