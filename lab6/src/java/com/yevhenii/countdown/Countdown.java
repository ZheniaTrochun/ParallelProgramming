package com.yevhenii.countdown;

public interface Countdown {

    boolean isBlocked();

    void await();

    void release();
}
