using System;
using System.Threading;

namespace Sharp
{
    class Program
    {
        static void Main(string[] args)
        {
            int n = 10;
            int threadNum = 4;          

            CountdownEvent countdown = new CountdownEvent(threadNum);

            int[][] MF = Data.CreateMatrix(n);
            int[][] MG = Data.CreateMatrix(n);
            int h = 5;

            int[][] result = new int[n][];
            for (int i = 0; i < n; i++)
                result[i] = new int[n];

            StartMult(MF, MG, result, threadNum, countdown);

            countdown.Wait();

            MF = Data.MultByNum(result, h);

            Data.PrintMatrix(MF);

            Console.Read();
        }

        private static void RecursiveStart(int[][] a, int[][] b, int[][] result, CountdownEvent countdown, int i, int prev, int count, int threads, int additional)
        {
            int cnt = ((i == 0) ? count + additional : count);
            new Thread(() => Data.MultiplyPart(a, b, result, prev, prev + cnt + threads - 1, countdown)).Start();

            if (i != 0)
                RecursiveStart(a, b, result, countdown, i - 1, prev + cnt - 1, count, threads, additional);
        }

        private static void StartMult(int[][] a, int[][] b, int[][] result, int threads, CountdownEvent countdown)
        {
            int n = a.Length;
            int count = n / threads;
            int additional = n % threads;

            RecursiveStart(a, b, result, countdown, threads - 1, 0, count, threads, additional);
        }
    }
}
