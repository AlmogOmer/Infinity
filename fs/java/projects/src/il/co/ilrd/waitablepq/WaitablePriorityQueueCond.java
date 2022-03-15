package il.co.ilrd.waitablepq;

import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class WaitablePriorityQueueCond<T> {
    private Queue<T> queue;
    private int capacity;
    private ReentrantLock lock;
    private Condition condFull;
    private Condition condEmpty;

    public WaitablePriorityQueueCond() {
        this(16,null);
    }

    public WaitablePriorityQueueCond(int capacity) {
        this(capacity,null);
    }

    public WaitablePriorityQueueCond(int capacity, Comparator<? super T> comp) {
        if(capacity <= 0){
            throw new IllegalArgumentException();
        }

        lock = new ReentrantLock();
        condFull  = lock.newCondition();
        condEmpty  = lock.newCondition();
        queue = new PriorityQueue<>(capacity,comp);
        this.capacity = capacity;
    }

    public void enqueue(T data) {
        lock.lock();
        while (queue.size() == capacity){
            try {
                condEmpty.await();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        
        queue.add(data);
        condFull.signalAll();
        lock.unlock();

    }

    public T dequeue() {
        T data;
        lock.lock();
        while (queue.isEmpty()){
            try {
                condFull.await();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        data = queue.poll();
        condEmpty.signalAll();
        lock.unlock();

        return data;
    }

    public boolean remove(T data) {
        boolean ret;
        lock.lock();
        ret = queue.remove(data);
        condEmpty.signalAll();
        lock.unlock();

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
