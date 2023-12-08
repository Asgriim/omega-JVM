
import java.io.Serializable;
interface A {
    int typ();
}
// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Aboba implements A {
    public static int sus = 0;
    public static int s = 1;
    public static void addSus() {
        sus++;
    }
    public static void main(String[] args) {
        // Press Alt+Enter with your caret at the highlighted text to see how
        // IntelliJ IDEA suggests fixing it.
        System.out.printf("Hello and welcome!");
        addSus();
        // Press Shift+F10 or click the green arrow button in the gutter to run the code.
        for (int i = 1; i <= 5; i++) {
            System.out.println("Hello and welcome!");
        }
    }

    @Override
    public int typ() {
        return 0;
    }
}