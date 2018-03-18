using System;
using System.Threading;

namespace Sharp
{
    class Data
    {
        public static int[][] CreateMatrix(int n)
        {
            int[][] m = new int[n][];

            for (int i = 0; i < n; i++)
            {
                m[i] = new int[n];

                for (int j = 0; j < n; j++)
                    m[i][j] = 1;
            }

            return m;
        }

        public static void PrintMatrix(int[][] m)
        {
            for (int i = 0; i < m.Length; i++)
            {
                for (int j = 0; j < m[i].Length; j++)
                    Console.Write(m[i][j] + "\t");
                Console.WriteLine();
            }
        }

        public static void MultiplyPart(int[][] a, int[][] b, int[][] result, int start, int end, CountdownEvent countdown)
        {
            for (int row = start; row < end; row++)
                for (int col = 0; col < b.Length; col++)
                {
                    result[row][col] = 0;
                    for (int k = 0; k < b.Length; k++)
                        result[row][col] += a[row][k] * b[k][col];
                }
            countdown.Signal();
        }

        public static int[][] MultByNum(int[][] m, int h)
        {
            for (int i = 0; i < m.Length; i++)
                for (int j = 0; j < m.Length; j++)
                    m[i][j] *= h;

            return m;
        }
    }
}