class lol implements Runnable {

    @Override
    public void run() {
        stupid();
    }

    public void stupid() {
        int i=0;
        while (i<10000) {
            i = i + 1;
        }
        System.out.println("done");
    }

}

class GenerateRunnables {
 
    public static void main(String[] args) throws InterruptedException{
        for (int i = 0; i<1800; i++) {
            Thread.sleep(200);
            new lol().stupid();
            Thread.sleep(200);
            if (i > 1500) {
                Thread.sleep(500);
            }
            
        }
    }
}