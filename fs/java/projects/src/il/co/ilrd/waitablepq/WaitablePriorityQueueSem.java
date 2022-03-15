package il.co.ilrd.waitablepq;

import java.util.Comparator;
import java.util.Objects;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.concurrent.Semaphore;

public class WaitablePriorityQueueSem<T> {
    private Queue<T> queue;
    private int capacity;
    private Semaphore sema;

    public WaitablePriorityQueueSem() {

    }

    public WaitablePriorityQueueSem(int capacity) {
        sema = new Semaphore(0);
    }

    public WaitablePriorityQueueSem(int capacity, Comparator<? super T> comp) {

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
