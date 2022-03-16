package il.co.ilrd.waitablepq;

import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class WaitablePriorityQueueCond<T> {
    private volatile Queue<T> queue;
    private final int capacity;
    private final ReentrantLock lock;
    private final Condition condFull;
    private final Condition condEmpty;

    public WaitablePriorityQueueCond() {
        this(11,null);
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
        try{
            while (queue.size() == capacity){
                condEmpty.await();
            }
            queue.add(data);
            condFull.signal();
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }

        finally{
            lock.unlock();
        }
        
    }

    public T dequeue() {
        T data = null;
        lock.lock();
        try{
            while (queue.isEmpty()){
                condFull.await();
            }
    
            data = queue.poll();
            condEmpty.signal();
            return data;

        } catch (InterruptedException e) {
            e.printStackTrace();
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
            condEmpty.signal();
            return ret;
        }

        finally{
            lock.unlock();
        }
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
