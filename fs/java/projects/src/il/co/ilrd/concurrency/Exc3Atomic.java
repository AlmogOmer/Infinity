package il.co.ilrd.concurrency;

import java.util.concurrent.atomic.AtomicBoolean;

public class Exc3Atomic {
    public static AtomicBoolean flag = new AtomicBoolean(false);
    public static void main(String[] args) {
        Producer pro = new Producer();
        Consumer con = new Consumer();
        pro.start();
        con.start();
        
        try {
            pro.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        try {
            con.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
        
}

class Producer extends Thread {
    public void run() {
    	int i;
        for(i=0; i<30;++i){
            while(Exc3Atomic.flag.get()){};
            System.out.println("Ping!"); /*get in only in flag = false*/
            Exc3Atomic.flag.set(true);
        }
    }

}

class Consumer extends Thread {
    public void run() {
        int i;
        for(i=0; i<30;++i){
            while(!Exc3Atomic.flag.get()){};
            System.out.println("Pong!"); /*get in only in flag = true*/
            Exc3Atomic.flag.set(false);
        }
    	
    }

}
