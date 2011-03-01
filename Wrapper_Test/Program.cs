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
                if (String.IsNullOrEmpty(input))
                {
                    Console.WriteLine("Invalid test number entered.");
                }
                else
                {
                    switch (input.ToLower())
                    {
                        case "1":
                            GdbMgmtTest.Run();
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
        }

        private static void WriteIntro()
        {
            Console.WriteLine("Enter a number for the test to run.  Type ALL to execute all tests, EXIT to finish.\n");
            Console.WriteLine("1: Geodatabase Management (Create/Open/Close/Delete)");
        }
    }
}
