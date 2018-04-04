package com.yevhenii.lab6.countdown;


public class CountdownImpl implements Countdown {
    volatile private int counter;

    public CountdownImpl(int counter) {
        this.counter = counter;
    }

    @Override
    public boolean isBlocked() {

        return counter != 0;
    }

    @Override
    synchronized public void await() {
        if (isBlocked()) {
            try {
                wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    @Override
    synchronized public void release() {
        counter--;

        if (counter == 0)
            notify();
    }
}
