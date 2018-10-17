using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;

namespace LogParser
{
   class Program
   {
      static IEnumerable<int> Slice(int[] array, int from, int to)
      {
         for (int i = from; i < to; i++)
            yield return array[i];
      }

      static void Main(string[] args)
      {
         var assembly = Assembly.GetExecutingAssembly();
         var stream = assembly.GetManifestResourceStream("LogParser.bathroom_humidity_samples.txt");

         var intValues = Parse(stream).ToArray();
         var n = intValues.Length;
         var step = 20;

         Console.WriteLine("namespace Median");
         Console.WriteLine("{");
         Console.WriteLine("   public static class Data");
         Console.WriteLine("   {");
         Console.WriteLine("      public static int[] Humidity = new[]");
         Console.WriteLine("      {");

         for (int i = 0; i < n; i += step)
         {
            var slice = Slice(intValues, i, Math.Min(i + step, n));
            Console.WriteLine("         " + string.Join(", ", slice) + ",");
         }

         Console.WriteLine("      };");
         Console.WriteLine("   }");
         Console.WriteLine("}");
      }

      private static IEnumerable<int> Parse(Stream stream)
      {
         using (var sr = new StreamReader(stream))
         {
            string line;
            while ((line = sr.ReadLine()) != null)
            {
               if (line.StartsWith("="))
                  continue;

               var vals = line.Split('%');

               yield return (int)(decimal.Parse(vals[0]) * 10);
            }
            Console.WriteLine(line);
         }
      }
   }
}
