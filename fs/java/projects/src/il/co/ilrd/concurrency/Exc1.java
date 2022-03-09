package il.co.ilrd.concurrency;

public class Exc1 {
    public static void main(String[] args) {
        MyThread t1 = new MyThread();
        t1.start();
        try {
            Thread.sleep(1);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        t1.interrupt(); 

        MyRunnable r1 = new MyRunnable();
        Thread t2 = new Thread(r1);
        t2.start();
        try {
            Thread.sleep(1);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        r1.mystop(); 

    }
}

class MyRunnable implements Runnable {
    private volatile boolean running = true;

    public void run() {
        while (running) {
            System.out.println(Thread.currentThread().getName() + " running.");
        }
        System.out.println(Thread.currentThread().getName() + " Stopped.");
    }

    public void mystop()
    {
        running = false;
    }
}
    
class MyThread extends Thread {
    public void run() {
    	while (!isInterrupted()) {
            System.out.println(Thread.currentThread().getName() + " running.");
        }
        System.out.println(Thread.currentThread().getName() + " Stopped.");
    }

}



