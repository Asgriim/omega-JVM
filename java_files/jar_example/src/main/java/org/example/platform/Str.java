package org.example.platform;

public class Str {
    private char[] buff;
    private int len;
    private int capacity;

    public Str(char[] string) {
        len = string.length;
        capacity = (len + 1) * 2;
        buff = new char[capacity];

        int i = 0;
        while (i < len) {
            buff[i] = string[i];
            i++;
        }
    }

    public void add(char c) {
        int nl = this.len + 1;
        if (nl >= this.capacity) {
            this.capacity = this.capacity * 2;
            char[] t = new char[this.capacity];
            int i = 0;
            while (i < this.len) {
                t[i] = buff[i];
                i++;
            }
            buff = t;
        }

        buff[len] = c;
        len++;
    }

    public void add(Str s) {
        int nl = this.len + s.len;

        if (nl >= this.capacity) {
            this.capacity = nl + 10;
            char[] t = new char[this.capacity];
            int i = 0;
            while (i < this.len) {
                t[i] = buff[i];
                i++;
            }
            buff = t;
        }

        int i = 0;

        while (i < s.len) {
            buff[len] = s.buff[i];
            len++;
            i++;
        }
    }

    public char[] getBuff() {
        return buff;
    }

    public int getLen() {
        return len;
    }
}
