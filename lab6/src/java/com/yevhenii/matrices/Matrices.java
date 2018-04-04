package com.yevhenii.matrices;

import java.util.Arrays;

public class Matrices {

    public static int[][] generateMatrix(int size) {
        int[][] m = new int[size][size];

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                m[i][j] = 1;
            }
        }

        return m;
    }

    public static int[][] trans(int[][] m) {
        int[][] tmp = new int[m.length][m[0].length];

        for (int i = 0; i < m.length; i++) {
            for (int j = 0; j < m[0].length; j++) {
                tmp[i][j] = m[j][i];
            }
        }

        return tmp;
    }

    public static void multiplyPart(int[][] m1, int[][] m2, int[][] res, int start, int end) {
        for (int i = start; i < end; i++) {
            for (int j = 0; j < m2.length; j++) {
                res[i][j] = 0;

                for (int k = 0; k < m2[0].length; k++) {
                    res[i][j] += m1[i][k] * m2[k][j];
                }
            }
        }
    }

    public static int[][] sort(int[][] m) {
        for (int[] aM : m) {
            Arrays.sort(aM);
        }

        return m;
    }

    public static int[][] sum(int[][] to, int[][] subj) {
        int[][] res = new int[to.length][to[0].length];

        for (int i = 0; i < to.length; i++) {
            for (int j = 0; j < to[0].length; j++) {
                res[i][j] = to[i][j] + subj[i][j];
            }
        }

        return res;
    }

    public static String toString(int[][] m) {
        StringBuilder sb = new StringBuilder();

        for (int i = 0; i < m.length; i++) {
            for (int j = 0; j < m[0].length; j++) {
                sb.append(String.format("%d\t", m[i][j]));
            }
            sb.append("\n");
        }

        return sb.toString();
    }
}
