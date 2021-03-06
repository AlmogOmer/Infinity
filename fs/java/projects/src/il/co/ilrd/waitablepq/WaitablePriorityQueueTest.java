/*Reviewer : Dolev*/

package il.co.ilrd.waitablepq;

import java.util.Comparator;

public class WaitablePriorityQueueTest {
    public static void main(String[] args) {
        final int NUM_OF_THREADS = 10;
        //WaitablePriorityQueueSem<Integer> semq = new WaitablePriorityQueueSem<>();
        //WaitablePriorityQueueCond<Integer> conq = new WaitablePriorityQueueCond<>();
        Comparator<Integer> comparator = (o1, o2) -> o1.compareTo(o2);
        //WaitablePriorityQueueCond<Integer> conq = new WaitablePriorityQueueCond<>(7,comparator);
        WaitablePriorityQueueSem<Integer> semq = new WaitablePriorityQueueSem<>(7,comparator);
        Runnable p = new Runnable() {
            @Override
            public void run() {
                for(int i=0; i<5;++i){
                    semq.enqueue(i);
                    System.out.println("adding :" + i);
                    System.out.println("size is :" + semq.size());
                }
            }
        };

        Runnable c = new Runnable() {
            @Override
            public void run() {
                for(int i=0; i<5;++i) {
                    System.out.println("removing: " + semq.dequeue() + " size " + semq.size());
                }
            }
        };


        Thread[] prod = new Thread[NUM_OF_THREADS];
        Thread[] cons = new Thread[NUM_OF_THREADS];

        for (int i = 0; i < NUM_OF_THREADS; ++i) {
            prod[i] = new Thread(p);
            cons[i] = new Thread(c);

            prod[i].start();
            cons[i].start();
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

/*package il.co.ilrd.waitablepq;

import java.io.IOException;
import java.util.Scanner;

public class WaitablePriorityQueueTest {
	private static final int WAITABLE_SIZE = 5;
	private static final int NUM_OF_PRODUCERS = 10;
	private static final int NUM_OF_CONSUMERS = 10;
	private static WaitablePriorityQueueSem<Integer> waitableQueue = new WaitablePriorityQueueSem<>(WAITABLE_SIZE);
	private static boolean succeeded = true;
	private static int counter_failed = 0;
	
	public static void printSucceeded(){
		System.out.println("\n\n\nSucceeded ");
	}
	
	public static void printFailed(){
		System.out.println("\n\n\nFailed ");
		succeeded = false;
		counter_failed++;
	}
	
	public static void checkSuccess(){
		if(true == succeeded){
			System.out.println("\t\t\tAll Tests Passed! ");
		}
		else{
			System.out.println("\t\t\t" + counter_failed + " Test Failled! ");
		}
	}
	
	public static void testEmptyWaitable() throws InterruptedException {
		System.out.println("\n\nTest EmptyWaitable\n\n");
		
		Reader t1 = new Reader();
		Writer t2 = new Writer();
		
		System.out.println("Reader Trying to read From Empty Queue");
    	t1.start();
    	for(int i = 0; i < 3; i++) {
    		System.out.println("Sleeping");
    		Thread.sleep(2000);
    	}
    	
    	System.out.println("Writer Write(Expected Read Will Read)");
    	t2.start();
    	
	}
	
	public static void testFullWaitable() throws InterruptedException {
		System.out.println("\n\nTest FullWaitable\n\n");
		
		Reader t1 = new Reader();
		Writer t2 = new Writer();
		
		for(int i = 0; i < WAITABLE_SIZE; i++) {
			t2.run();
		}
    	
		t2.start();
		
		System.out.println("Writer trying to write from full queue");
		
    	for(int i = 0; i < 3; i++) {
    		System.out.println("Sleeping");
    		Thread.sleep(2000);
    	}
    	
    	System.out.println("Reader reads(Expected Writer Will Write)");
    	t1.start();
    	
    	for(int i = 0; i < WAITABLE_SIZE; i++) {
    		t1.run();
    	}
    	
	}
	
	public static void testSyncThreads() throws InterruptedException {
		System.out.println("\n\nTest SyncThreads\n\n");
		
		Reader[] readers = new Reader[WAITABLE_SIZE * 2];
		Writer[] writers = new Writer[WAITABLE_SIZE * 2];
		int counterReaders = 0;
		int counterWriters = 0;
		
		int i = 0;
		
        for (Reader reader : readers) {
        	readers[i] = new Reader();
        	readers[i].start();
        	counterReaders++;
        	i++;
        }
        
        i = 0;
        
        for (Writer writer : writers) {
        	writers[i] = new Writer();
        	writers[i].start();
        	counterWriters++;
        	i++;
        }
        
        i = 0;
        
        for (Reader reader : readers) {
            try {
            	readers[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        
        i = 0;
        
        for (Writer writer : writers) {
            try {
            	writers[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        
        
        Thread.sleep(2000);
        System.out.println("\n\nSIZE IS \n\n" + waitableQueue.size());
        if(counterWriters == counterReaders && waitableQueue.size() == 0 && waitableQueue.isEmpty()) {
        	printSucceeded();
        }
        else {
        	printFailed();
        }
	}
	
	public static void testRemove() throws InterruptedException {
		System.out.println("\n\nTest Remove\n\n");
		
		ReaderSpecific []readers = new ReaderSpecific[WAITABLE_SIZE];
		Writer []writers = new Writer[WAITABLE_SIZE];
		
		int i = 0;
		
        for (Writer writer : writers) {
        	writers[i] = new Writer();
        	writers[i].start();
        	i++;
        }
        
        i = 0;
        
        for (Writer writer : writers) {
            try {
            	writers[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        
        i = 0;
        for (ReaderSpecific reader : readers) {
        	readers[i] = new ReaderSpecific();
        	readers[i].start();
        	i++;
        }
        
        i = 0;
        for (ReaderSpecific reader : readers) {
            try {
            	readers[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        
        Thread.sleep(2000);
        
        if(waitableQueue.size() == 0 && waitableQueue.isEmpty()) {
        	printSucceeded();
        }
        else {
        	printFailed();
        }
        
		
	}
	
	public static void main (String[] args) throws InterruptedException {
		testEmptyWaitable();
		testFullWaitable();
		testSyncThreads();
		testRemove();
	}
	
	public static class Reader extends Thread {
	    @Override
		public void run() {
	    	waitableQueue.dequeue();
	    	System.out.println("Succeeded to dequeue");
	    }
	}

	public static class ReaderSpecific extends Thread {
		@Override
		public void run() {
	    	waitableQueue.remove(--Writer.j);
	    	System.out.println("Succeeded to dequeue" + Writer.j);
	    }
	}
	
	public static class Writer extends Thread {
	    public static volatile int j = 0;
		@Override
		public void run() {
	    	waitableQueue.enqueue(j++);
	    	System.out.println("Succeeded to enqueue ");
	    }
	}

}
*/
