package org.example;


import org.example.platform.Console;
import org.example.platform.DllImport;
import org.example.platform.Str;

// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {
    public static void main(String[] args) {
        char[] a = "in 2 str: ".toCharArray();
        Str str0 = new Str(a);
        Str in = Console.readLine();
        str0.add(in);
        Console.print(str0);
    }



}
