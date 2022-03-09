package il.co.ilrd.concurrency;

import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.Semaphore;



public class Exc3LinkedSem {
    public static List<Object> list1 = new LinkedList<>();
    public static Object obj1 = new Object();
    public static final Semaphore sem = new Semaphore(5);
    
    public static void main(String[] args) {
        final int NUM_OF_THREADS = 10;
        Producer3[] producer1 = new Producer3[NUM_OF_THREADS];
        Consumer3[] consumer1 = new Consumer3[NUM_OF_THREADS];

        for (int i = 0; i < NUM_OF_THREADS; ++i) {
            producer1[i] = new Producer3();
            consumer1[i] = new Consumer3();

            producer1[i].start();
            consumer1[i].start();
        }
        for (int i = 0; i < NUM_OF_THREADS; ++i) {

            try {
                producer1[i].join();
                consumer1[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

    }
        
}

class Producer3 extends Thread {
    public void run() {
    	int i;
        for(i=0; i<30;++i){
            synchronized (Exc3LinkedSem.obj1) {
                System.out.println("insert obj");
                Exc3LinkedSem.list1.add(Exc3LinkedSem.obj1);
            }
            Exc3LinkedSem.sem.release();

        }
    }

}

class Consumer3 extends Thread {
    public void run() {
        int i;
        for(i=0; i<30;++i){
            try {
                Exc3LinkedSem.sem.acquire();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            synchronized (Exc3LinkedSem.obj1) {
                System.out.println("removing obj from list");
                Exc3LinkedSem.list1.remove(Exc3LinkedSem.obj1);
            }

        }
    	
    }

}
 
