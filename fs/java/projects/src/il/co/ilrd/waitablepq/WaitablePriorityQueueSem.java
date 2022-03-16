package il.co.ilrd.waitablepq;

import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.concurrent.Semaphore;

public class WaitablePriorityQueueSem<T> {
    private volatile Queue<T> queue;
    private final int capacity;
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
        synchronized(this){
            queue.add(data);
            semFull.release();
        }
    }

    public T dequeue() {
        T data;
        try {
            semFull.acquire();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        synchronized(this){
            data = queue.poll();
            semEmpty.release();
        }

        return data;
    }

    public boolean remove(T data) {
        boolean ret;
        synchronized(this){
            ret = queue.remove(data);
            semEmpty.release();
        }

        return ret;

    }

    public int size() {
        synchronized (this) {
            return queue.size();
        }
    }

    public boolean isEmpty() {
        synchronized (this) {
            return queue.isEmpty();
        }
    }
}
