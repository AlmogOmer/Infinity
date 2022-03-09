package il.co.ilrd.concurrency;

import java.util.concurrent.Semaphore;

public class Exc3Sem {
    public static final Semaphore proSem = new Semaphore(1);
    public static final Semaphore conSem = new Semaphore(0);
    public static void main(String[] args) {
        Producer1 pro1 = new Producer1();
        Consumer1 con1 = new Consumer1();
        pro1.start();
        con1.start();
        
        try {
            pro1.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        try {
            con1.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
        
}

class Producer1 extends Thread {
    public void run() {
    	int i;
        for(i=0; i<30;++i){
            try {
                Exc3Sem.conSem.acquire();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println("Ping!"); 
            Exc3Sem.proSem.release();
        }
    }

}

class Consumer1 extends Thread {
    public void run() {
        int i;
        for(i=0; i<30;++i){
            try {
                Exc3Sem.proSem.acquire();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println("Pong!"); 
            Exc3Sem.conSem.release();
        }
    	
    }

}

