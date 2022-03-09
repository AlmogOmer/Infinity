package il.co.ilrd.concurrency;

//import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.ReentrantLock;

public class Exc2 {
    public static int counter = 0;
    private final static ReentrantLock lock = new ReentrantLock();
    public static void add(){
        lock.lock();
        ++counter;   
        lock.unlock();
    }

    public static void main(String[] args) {
        rThread th1 = new rThread();
        rThread th2 = new rThread();
        long start = System.currentTimeMillis();
        th1.start();
        th2.start();
        
        try {
            th1.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        try {
            th2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        
        long end = System.currentTimeMillis();
        
        System.out.println(counter);
        System.out.println(end-start);

    }
    
}

class rThread extends Thread {
    public void run() {
    	int i;
        for(i=0; i<10000000; ++i){
            Exc2.add();
        }
    }

}


/* no synchro : 5
synchro method: 309
synchro block: 216
atomic : 366
reentrant : 460*/