package org.example;


import org.example.platform.Console;
import org.example.platform.DllImport;
import org.example.platform.Str;

// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {
    public static void main(String[] args) {
        char[] a = {'a'};
        Str str0 = new Str(a);
        Str in = Console.readLine();
        Console.print(in);
    }



}
