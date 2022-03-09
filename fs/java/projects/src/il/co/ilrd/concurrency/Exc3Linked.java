package il.co.ilrd.concurrency;

import java.util.LinkedList;
import java.util.List;


public class Exc3Linked {
    public static List<Object> list = new LinkedList<>();
    public static Integer a = 0;
    
    public static void main(String[] args) {
        final int NUM_OF_THREADS = 10;
        Producer2[] producer = new Producer2[NUM_OF_THREADS];
        Consumer2[] consumer = new Consumer2[NUM_OF_THREADS];

        for (int i = 0; i < NUM_OF_THREADS; ++i) {
            producer[i] = new Producer2();
            consumer[i] = new Consumer2();

            producer[i].start();
            consumer[i].start();
        }
        for (int i = 0; i < NUM_OF_THREADS; ++i) {

            try {
                producer[i].join();
                consumer[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

    }
        
}

class Producer2 extends Thread {
    public void run() {
    	int i;
        for(i=0; i<30;++i){
            synchronized (Exc3Linked.list) {
                ++Exc3Linked.a;
                System.out.println("insert : " + Exc3Linked.a);
                Exc3Linked.list.add(Exc3Linked.a);
            }

        }
    }

}

class Consumer2 extends Thread {
    public void run() {
        int i;
        for(i=0; i<30;++i){
            synchronized (Exc3Linked.list) {
                if(!Exc3Linked.list.isEmpty()){
                    System.out.println("removing : " + Exc3Linked.a);
                    Exc3Linked.list.remove(Exc3Linked.a);
                }
                
            }

        }
    	
    }

}
 

