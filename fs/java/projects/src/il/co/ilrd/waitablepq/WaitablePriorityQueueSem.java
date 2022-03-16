/*Reviewer : Dolev*/
package il.co.ilrd.waitablepq;

import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.ReentrantLock;

public class WaitablePriorityQueueSem<T> {
    private volatile Queue<T> queue;
    private final int capacity;
    private final ReentrantLock lock;
    private final Semaphore semFull;
    private final Semaphore semEmpty;

    public WaitablePriorityQueueSem() {
        this(11,null);
    }

    public WaitablePriorityQueueSem(int capacity) {
        this(capacity,null);
    }

    public WaitablePriorityQueueSem(int capacity, Comparator<? super T> comp) {
        if(capacity <= 0){
            throw new IllegalArgumentException();
        }

        lock = new ReentrantLock();
        semFull = new Semaphore(0);
        semEmpty = new Semaphore(capacity);
        queue = new PriorityQueue<>(capacity,comp);
        this.capacity = capacity;
    }

    public void enqueue(T data) {
        try {
            semEmpty.acquire();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        lock.lock();
        try{
            queue.add(data);
            semFull.release();
        }
        
        finally{
            lock.unlock();
        }
    }

    public T dequeue() {
        T data;
        try {
            semFull.acquire();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        lock.lock();
        try{
            data = queue.poll();
            semEmpty.release();
        }

        finally{
            lock.unlock();
        }

        return data; 

    }

    public boolean remove(T data) {
        boolean ret = false;
        lock.lock();
        try{
            ret = queue.remove(data);
            semEmpty.release();
        }

        finally{
            lock.unlock();
        }

        return ret;

    }

    public int size() {
        int ret = 0;
        lock.lock();
        try{
            ret = queue.size();
        }

        finally{
            lock.unlock();
        }
        
        return ret;
    }

    public boolean isEmpty() {
        boolean ret = false;
        lock.lock();
        try{
            ret = queue.isEmpty();
        }

        finally{
            lock.unlock();
        }
        
        return ret;
    }
}
