package il.co.ilrd.waitablepq;

public class WaitablePriorityQueueTest {
    public static void main(String[] args) {
        final int NUM_OF_THREADS = 30;
        //WaitablePriorityQueueSem<Integer> semq = new WaitablePriorityQueueSem<>();
        WaitablePriorityQueueCond<Integer> conq = new WaitablePriorityQueueCond<>();

        Runnable p = new Runnable() {
            @Override
            public void run() {
                for(int i=0; i<30;++i){
                    conq.enqueue(i);
                    System.out.println("adding :" + i);
                    System.out.println("size is :" + conq.size());
                }
            }
        };

        Runnable c = new Runnable() {
            @Override
            public void run() {
                for(int i=0; i<30;++i) {
                    System.out.println("removing: " + conq.dequeue() + " size " + conq.size());
                }
            }
        };


        Thread[] prod = new Thread[NUM_OF_THREADS];
        Thread[] cons = new Thread[NUM_OF_THREADS];

        for (Thread pr : prod) {
            pr = new Thread(p);
            pr.start();
        }

        for (Thread co : cons) {
            co = new Thread(c);
            co.start();
        }

        for (int i = 0; i < NUM_OF_THREADS; ++i) {
            try {
                prod[i].join();
                cons[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

}
