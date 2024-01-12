
import java.io.Serializable;
interface A {
    int typ();
}
// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Aboba implements A {
    public static int sus = -1;
    public static int s = 2;

    public static int addSus() {
        sus++;
        return sus;
    }

    public static void main(String[] args) {
        addSus();
        System.out.println("Hello and welcome!");
        System.out.println(sus);
    }

    @Override
    public int typ() {
        return 0;
    }
}
