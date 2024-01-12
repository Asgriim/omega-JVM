public class Hello {

    @DllImport("libc")
    static native int write(int fd, byte[] data, int length);

    @DllImport("libc")
    static native int read(int fd, byte[] data, int length);

    public static void main(String args[]) {
        System.out.println("Hello world!");
    }
}