package org.example;

public class Y extends X{
    private int y = 2;

    public Y() {
    }

    public Y(int y) {
        this.y = y;
    }

    @Override
    public int getI() {
            return super.getI() + 14;
        }

    public int getY() {
        return y;
    }

    public void setY(int y) {
        this.y = y;
    }
}
