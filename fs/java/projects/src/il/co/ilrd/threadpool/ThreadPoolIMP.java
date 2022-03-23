/*Reviewer : Ofek*/
package il.co.ilrd.threadpool;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.concurrent.Callable;
import java.util.concurrent.CancellationException;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Executor;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

import il.co.ilrd.waitablepq.WaitablePriorityQueueCond;

public class ThreadPoolIMP implements Executor {
    public enum Priority {
        LOW,
        MEDIUM,
        HIGH;
    }
    
    private WaitablePriorityQueueCond<Task<?>> tasks;
    private List<ThreadImp> threads;
    private int numOfThreads = 0;
    private int HIGHESTPRI = Priority.HIGH.ordinal() + 1;
    private int LOWESTPRI = Priority.LOW.ordinal() - 1;
    private final ReentrantLock lockP = new ReentrantLock();
    private final Condition condP = lockP.newCondition();
    private final Semaphore sem = new Semaphore(0);
    private boolean isShutdown = false;

    public ThreadPoolIMP(int numOfThreads){
        if (numOfThreads < 1) {
            throw new IllegalArgumentException();
        }
        this.numOfThreads = numOfThreads;
        tasks = new WaitablePriorityQueueCond<>();
        threads = new ArrayList<>();

        addThreads(numOfThreads);

    }

    @Override
    public void execute(Runnable command) {
        Objects.requireNonNull(command);
        Task<?> task = new Task<>(Executors.callable(command), 1);
        tasks.enqueue(task);  
    }

    public <T> Future<T> submit(Callable<T> callable, Priority priority){
        Objects.requireNonNull(callable);
        return submitImp(callable, priority.ordinal());
    }
    
    public <T> Future<T> submit(Callable<T> callable){
        Objects.requireNonNull(callable);
        return submitImp(callable, 1);
    }

    public Future<Object> submit(Runnable runnable, Priority priority){
        Objects.requireNonNull(runnable);
        return submitImp(Executors.callable(runnable), priority.ordinal());
    }
    public Future<Object> submit(Runnable runnable){
        Objects.requireNonNull(runnable);
        return submitImp(Executors.callable(runnable), 1);
    }

    public <T> Future<T> submit(Runnable runnable, Priority priority, T result){
        Objects.requireNonNull(runnable);
        return submitImp(Executors.callable(runnable, result), priority.ordinal());
    }

    public void setNumberOfThreads(int numOfThreads){
        if (numOfThreads < 1) {
            throw new IllegalArgumentException();
        }

        if (numOfThreads > this.numOfThreads){
            int diff = numOfThreads - this.numOfThreads;
            addThreads(diff);

        }

        else if(numOfThreads < this.numOfThreads){
            int diff = this.numOfThreads - numOfThreads;
            for (int i = 0; i < diff; ++i){
                killingtask(HIGHESTPRI);
            }
            
        }

        this.numOfThreads = numOfThreads;
    }

    public void pause(){
        for (int i = 0; i < numOfThreads ; ++i){
            Callable<Void> pausingTask = new Callable<>() {
                public Void call() throws Exception {
                    lockP.lock();
                    try{
                        condP.await();
                    }

                    finally{
                        lockP.unlock();
                    }
        
                    return null;
                    
                }
            };

            submitImp(pausingTask, HIGHESTPRI);
        }
    }

    public void resume(){
        lockP.lock();
        try{
            condP.signalAll();
        }

        finally{
            lockP.unlock();
        }
        
    }

    public void shutdown(){
        isShutdown = true;
        for (int i = 0; i < numOfThreads; ++i){
            killingtask(LOWESTPRI);
        }
    }

    public void awaitTermination() throws InterruptedException{
        try {
            sem.acquire(numOfThreads);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public boolean awaitTermination(long timeout, TimeUnit unit) throws InterruptedException{
        boolean result = false;
        try {
            result = sem.tryAcquire(numOfThreads, timeout, unit);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        return result;
    }

    private void addThreads(int addThreads) {
		for(int i = 0; i < addThreads; i++) {
			ThreadImp newThread = new ThreadImp();
			threads.add(newThread);
			newThread.start();
		}
	}

    private <T> Future<T> submitImp(Callable<T> callable, int priority){
        Task<T> task = new Task<>(callable, priority);
        tasks.enqueue(task); 
        return task.getFuture();
    }

    private <T> boolean removeTask(Task<T> task){
        return tasks.remove(task);
    }

    private void killingtask(int prioirity){
        Callable<Void> killingTask = new Callable<>() {
            public Void call() throws Exception {
                Thread.currentThread().interrupt();
                threads.remove(Thread.currentThread());
                if(isShutdown){
                    sem.release();
                }

                return null;
                
            }
        };

        submitImp(killingTask, prioirity);
        
    }


    private class ThreadImp extends Thread{
        @Override
        public void run() {
            while(!Thread.interrupted()){
                Task<?> task = tasks.dequeue();
                task.setcurrThread(Thread.currentThread());
                task.runTask();
            }
            
        }
        
    }




    private class Task<T> implements Comparable<Task<T>>{
        private final Callable<T> task;
        private final int priority;
        private Thread currThread;
        private final TaskFuture<T> taskFuture;
        private boolean isDone = false;
        private Exception executionException = null;
        private final ReentrantLock lock = new ReentrantLock();
        private final Condition cond = lock.newCondition();

        public Task(Callable<T> task, int priority){
           this.task = task;
           this.priority = priority;
           taskFuture = new TaskFuture<T>();
        }

        public void runTask(){
            try {
                taskFuture.retVal = task.call();
                isDone = true;
            } catch (Exception e) {
                executionException = e;
                e.printStackTrace();
            }
            lock.lock();
            try{
                cond.signal();
            }
            finally{
                lock.unlock();
            }
        }
        
        public Future<T> getFuture(){
            return taskFuture;
        }

        @Override
        public int compareTo(Task<T> other) {
            return (other.priority - this.priority);
        }

        public void setcurrThread(Thread thread) {
            currThread = thread;
        }


        private class TaskFuture<E> implements Future<E>{
            private T retVal = null;
            private boolean isCancelled = false;
          
        
            @Override
            public boolean cancel(boolean mayInterruptIfRunning) {
                isCancelled = removeTask(Task.this);
                if(!isDone() && !isCancelled() && mayInterruptIfRunning && (Task.this.currThread != null)){
                    Task.this.currThread.interrupt();
                    isCancelled = true;
                }
                Task.this.isDone = true;
                return isCancelled;
            }
        
            @Override
            public boolean isCancelled() {
                return isCancelled;
            }
        
            @Override
            public boolean isDone() {
                return Task.this.isDone;
            }
        
            @Override
            public E get() throws InterruptedException, ExecutionException {
                try {
                    return get(Long.MAX_VALUE, TimeUnit.DAYS);
                } catch (TimeoutException e) {
                    e.printStackTrace();
                }
                return null;
            }
        
            @Override
            public E get(long timeout, TimeUnit unit) throws InterruptedException, ExecutionException, TimeoutException {
                lock.lock();
                try{
                    while(!isDone){
                        if (isCancelled){
                            throw new CancellationException();
                        }

                        if(Task.this.executionException != null){
                            throw new ExecutionException(Task.this.executionException);
                        }

                        if (Thread.currentThread().isInterrupted()){
                            throw new InterruptedException();
                        }

                        if(cond.await(timeout, unit) == false){
                            throw new TimeoutException();
                        }
                        
                    }
                }

                finally{
                    lock.unlock();
                }
                
                return (E)retVal;
                
            }
        
        }

    }

    
}



