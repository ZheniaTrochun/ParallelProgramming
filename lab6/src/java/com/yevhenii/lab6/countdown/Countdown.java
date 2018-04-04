package com.yevhenii.lab6.countdown;

public interface Countdown {

    boolean isBlocked();

    void await();

    void release();
}
