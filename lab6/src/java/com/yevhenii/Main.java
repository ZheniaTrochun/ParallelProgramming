package com.yevhenii;

import com.yevhenii.countdown.Countdown;
import com.yevhenii.countdown.CountdownImpl;
import com.yevhenii.matrices.Matrices;
import com.yevhenii.threads.MatrixMultiplier;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        int size = 10;

        int[][] mg = Matrices.generateMatrix(size);
        int[][] ml = Matrices.generateMatrix(size);
        int[][] mh = Matrices.generateMatrix(size);

        int[][] tmp = new int[size][size];
        int[][] mf;

        Countdown countdown = new CountdownImpl(4);

//        tmp = MH * MG (in multiple threads)
        startMultiplication(mh, mg, tmp, size, countdown, 4);
//        MG = MG + TRANS(tmp) + TRANS(ML)
        mf = Matrices.sort(sumation(ml, mg, tmp, countdown));

        System.out.println("SORT(MG + TRANS(MH * MG) + TRANS(ML)) result: ");
        System.out.println(Matrices.toString(mf));
    }

    private static void startMultiplication(int[][] mh, int[][] mg, int[][] tmp,
                                                   int size, Countdown countdown, int num) {

        for (int i = 0; i < num; i++) {
            new Thread(
                    new MatrixMultiplier(mh, mg, tmp, i, (i + 1) * size / num, countdown))
                        .start();
        }
    }

    private static int[][] sumation(int[][] ml, int[][] mg, int[][] tmp, Countdown countdown) {

        int[][] sum = Matrices.sum(mg, Matrices.trans(ml));
        countdown.await();
        mg = Matrices.sum(sum, Matrices.trans(tmp));

        return mg;
    }
}
