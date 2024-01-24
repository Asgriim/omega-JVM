package org.example.platform;

public class Console {
    private static final char[] lineDelimiter = {'\n'};

    @DllImport("libc.so.6")
    private static native int write(int fd, char[] buf, int count);

    @DllImport("libc.so.6")
    private static native int read(int fd, char[] buf, int count);

    public static void print(Str s) {
        write(1, s.getBuff(), s.getLen());
    }

    public static void newLine(){
        write(1, lineDelimiter, lineDelimiter.length);
    }

    public static void println(Str s) {
        print(s);
        newLine();
    }

    public static Str readLine() {
        Str s = new Str("".toCharArray());
        char[] c = new char[1];
        c[0] = '\0';
        int count = 1;
        while (c[0] != lineDelimiter[0] && count == 1) {
            count = read(0,c, c.length);
            s.add(c[0]);
        }
        return s;
    }
}
