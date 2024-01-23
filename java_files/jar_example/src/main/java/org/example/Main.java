package org.example;


import org.example.platform.DllImport;

// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {
    public static int sus = -1;
    public static int s = 2;

    public static int addSus(int a, int i2) {
        System.out.println(sus);
        sus++;
        int[] arr = new int[5];
        arr[2] = a;
        System.out.println(arr[2]);
        return sus;
    }

    public static void main(String[] args) {
//         addSus(42,1);
        Y y1 = new Y(213);
        System.out.println(y1.getY());
        y1.setY(1488);
        System.out.println(y1.getI());
//        write(1,null,1);
//        Y y = new Y();
//        y.getI();
//        Y.setZ(1);
//         System.out.println(Y.get());
//         X.setZ(12);
//         System.out.println(Y.get());
    }

    @DllImport("libc.s0.6")
    public static native int write(int fd, char[] buf, int cout);

}
