package il.co.ilrd.waitablepq;

import java.util.Comparator;
import java.util.Objects;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class WaitablePriorityQueueCond<T> {
    private Queue<T> queue;
    private int capacity;
    private ReentrantLock lock;
    private Condition cond;

    public WaitablePriorityQueueCond() {
        this(16);
    }

    public WaitablePriorityQueueCond(int capacity) {
        this(capacity,null);
    }

    public WaitablePriorityQueueCond(int capacity, Comparator<? super T> comp) {
        if(capacity <= 0){
            throw new IllegalArgumentException();
        }

        lock = new ReentrantLock();
        cond  = lock.newCondition();
        queue = new PriorityQueue<>(capacity,comp);
        this.capacity = capacity;
    }

    public void enqueue(T data) {

    }

    public T dequeue() {
    }

    public boolean remove(T data) {

    }

    public int size() {

    }

    public boolean isEmpty() {

    }
}
