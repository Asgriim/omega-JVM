package org.example;


interface A {
    int typ();
}
// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main implements A {
    public static int sus = -1;
    public static int s = 2;

    public static int addSus(int a, int i2) {
        System.out.println(sus);
        sus++;
        int[] arr = new int[5];
        arr[0] = a;
        System.out.println(arr[0]);
        return sus;
    }

    public static void main(String[] args) {
        addSus(42,1);
    }

    @Override
    public int typ() {
        return 0;
    }
}
