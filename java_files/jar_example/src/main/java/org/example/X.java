package org.example;

public class X {

    private int i = 2;
    static int z = 42;


    public int getI() {
        return i;
    }

    static int get() {
        return z;
    }

    public static void setZ(int z) {
        X.z = z;
    }
}
