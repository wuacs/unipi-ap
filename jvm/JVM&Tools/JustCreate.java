class JustCreate {
    public static void main (String[] args) throws InterruptedException {
        int i = 0;
        while (i < 100_000_000) {
            Object c = new Object();
            if (i > 998 && i % 999 == 0) {
                System.out.printf("Object's created: %d ", i+1);
                Thread.sleep(50);
            }
        }
    }
}