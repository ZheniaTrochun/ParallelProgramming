package com.yevhenii.lab6.threads;

import com.yevhenii.lab6.matrices.Matrices;
import com.yevhenii.lab6.countdown.Countdown;

public class MatrixMultiplier implements Runnable {

    private int[][] m1;
    private int[][] m2;
    private int[][] tmp;
    private int start;
    private int end;
    private Countdown countdown;

    public MatrixMultiplier(int[][] m1, int[][] m2, int[][] tmp, int start, int end, Countdown countdown) {
        this.m1 = m1;
        this.m2 = m2;
        this.tmp = tmp;
        this.start = start;
        this.end = end;
        this.countdown = countdown;
    }

    public int[][] getM1() {
        return m1;
    }

    public void setM1(int[][] m1) {
        this.m1 = m1;
    }

    public int[][] getM2() {
        return m2;
    }

    public void setM2(int[][] m2) {
        this.m2 = m2;
    }

    public int[][] getTmp() {
        return tmp;
    }

    public void setTmp(int[][] tmp) {
        this.tmp = tmp;
    }

    public int getStart() {
        return start;
    }

    public void setStart(int start) {
        this.start = start;
    }

    public int getEnd() {
        return end;
    }

    public void setEnd(int end) {
        this.end = end;
    }

    public Countdown getCountdown() {
        return countdown;
    }

    public void setCountdown(Countdown countdown) {
        this.countdown = countdown;
    }

    @Override
    public void run() {
        Matrices.multiplyPart(m1, m2, tmp, start, end);

        countdown.release();
    }
}
