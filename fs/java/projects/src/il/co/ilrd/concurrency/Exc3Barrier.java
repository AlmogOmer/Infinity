package il.co.ilrd.concurrency;

import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class Exc3Barrier {
    public static final Semaphore sem = new Semaphore(0);
    public final static ReentrantLock lock = new ReentrantLock();
    public static Condition cond  = lock.newCondition(); 
    public static volatile int global = 0;
    public static void main(String[] args) {
        final int NUM_OF_CON = 10;
        Producer4 producer2 = new Producer4();
        Consumer4[] consumer2 = new Consumer4[NUM_OF_CON];

        for (int i = 0; i < NUM_OF_CON; ++i) {
            consumer2[i] = new Consumer4();
            consumer2[i].start();
        }
            
        producer2.start();
        try {
            producer2.join();
        } catch (InterruptedException e1) {
            e1.printStackTrace();
        }

        for (int i = 0; i < NUM_OF_CON; ++i) {
            try {
                consumer2[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
        
}

class Producer4 extends Thread {
    public void run() {
        while(true){
            for (int i = 0; i < 10; ++i) {
                try {
                    Exc3Barrier.sem.acquire();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }

            ++Exc3Barrier.global;
            System.out.println("producer wrote: " + Exc3Barrier.global);

            Exc3Barrier.lock.lock();
            Exc3Barrier.cond.signalAll();
            Exc3Barrier.lock.unlock();      

        }
    }

}

class Consumer4 extends Thread {
    public void run() {
        while(true){
            Exc3Barrier.lock.lock();
            Exc3Barrier.sem.release();
            try {
                Exc3Barrier.cond.await();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            Exc3Barrier.lock.unlock();

            System.out.println("consumer read: " + Exc3Barrier.global);

        }
        
    }

}
 

