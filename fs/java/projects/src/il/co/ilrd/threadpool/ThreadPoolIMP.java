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
    private static final int HIGHEST_PRIORITY = Priority.HIGH.ordinal() + 1;
    private static final int LOWEST_PRIORITY = Priority.LOW.ordinal() - 1;
    private static final int DEFAULT_PRIORITY = Priority.MEDIUM.ordinal();
    private Semaphore semFinished = new Semaphore(0);
    private Semaphore semPause = null;


    public ThreadPoolIMP(int numOfThreads){
        if (numOfThreads < 0) {
            throw new IllegalArgumentException();
        }
        this.numOfThreads = numOfThreads;
        tasks = new WaitablePriorityQueueCond<>();
        threads = new ArrayList<>(numOfThreads);

        addThreads(numOfThreads);

    }

    @Override
    public void execute(Runnable command) {
        submit(command); 
    }

    public <T> Future<T> submit(Callable<T> callable, Priority priority){
        Objects.requireNonNull(callable);
        return submitImp(callable, priority.ordinal());
    }
    
    public <T> Future<T> submit(Callable<T> callable){
        Objects.requireNonNull(callable);
        return submitImp(callable, DEFAULT_PRIORITY);
    }

    public Future<Object> submit(Runnable runnable, Priority priority){
        Objects.requireNonNull(runnable);
        return submitImp(Executors.callable(runnable), priority.ordinal());
    }
    public Future<Object> submit(Runnable runnable){
        Objects.requireNonNull(runnable);
        return submitImp(Executors.callable(runnable), DEFAULT_PRIORITY);
    }

    public <T> Future<T> submit(Runnable runnable, Priority priority, T result){
        Objects.requireNonNull(runnable);
        return submitImp(Executors.callable(runnable, result), priority.ordinal());
    }

    public void setNumberOfThreads(int numOfThreads){
        if (numOfThreads < 1) {
            throw new IllegalArgumentException();
        }

        if (numOfThreads >= this.numOfThreads){
            int diff = numOfThreads - this.numOfThreads;
            addThreads(diff);

        }

        else {
            int diff = this.numOfThreads - numOfThreads;
            for (int i = 0; i < diff; ++i){
                Callable<Void> killingTask = new Callable<>() {
                    public Void call() throws Exception {
                        ThreadImp toRemove = (ThreadImp) Thread.currentThread();
                        toRemove.isRunning = false; 
                        threads.remove(toRemove);
                        return null;
                    }
                };
                submitImp(killingTask, HIGHEST_PRIORITY);
            }
            
        }

        this.numOfThreads = numOfThreads;
    }

    public void pause(){
        semPause = new Semaphore(0);
        for (int i = 0; i < numOfThreads ; ++i){
            Callable<Void> pausingTask = new Callable<>() {
                public Void call() throws Exception {
                    semPause.acquire();
                    return null;
                    
                }
            };

            submitImp(pausingTask, HIGHEST_PRIORITY);
        }
    }

    public void resume(){
        for(int i = 0; i < numOfThreads ; i++) {
			semPause.release();
		} 
    }

    public void shutdown(){
        for (int i = 0; i < numOfThreads; ++i){
            Callable<Void> killingTask = new Callable<>() {
                public Void call() throws Exception {
                    ThreadImp toRemove = (ThreadImp) Thread.currentThread();
                    toRemove.isRunning = false; 
                    threads.remove(toRemove);
                    semFinished.release();
                    return null;
                    
                }
            };
    
            submitImp(killingTask, LOWEST_PRIORITY);
        }
    }

    public void awaitTermination() throws InterruptedException{
        semFinished.acquire(numOfThreads);
    }

    public boolean awaitTermination(long timeout, TimeUnit unit) throws InterruptedException{
        return semFinished.tryAcquire(numOfThreads, timeout, unit);
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


    private class ThreadImp extends Thread{
        private boolean isRunning = true;
        @Override
        public void run() {
            while(isRunning){
                Task<?> task = tasks.dequeue();
                task.setCurrThread(Thread.currentThread());
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
        private T retVal = null;
        private boolean isCancelled = false;
        private boolean isRealDone = false;
        private final ReentrantLock lock = new ReentrantLock();
        private final Condition cond = lock.newCondition();

        public Task(Callable<T> task, int priority){
           this.task = task;
           this.priority = priority;
           taskFuture = new TaskFuture<T>();
        }

        public void runTask(){
            try {
                retVal = task.call();
                isDone = true;
                isRealDone = true;
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
            return (other.priority - priority);
        }

        private void setCurrThread(Thread thread) {
            currThread = thread;
        }


        private class TaskFuture<E> implements Future<E>{

            @Override
            public boolean cancel(boolean mayInterruptIfRunning) {
                isCancelled = removeTask(Task.this);
                if(!isDone() && !isCancelled() && mayInterruptIfRunning && currThread != null){
                    currThread.interrupt();
                    isCancelled = true;
                }

                isDone = true;
                return isCancelled;
            }
        
            @Override
            public boolean isCancelled() {
                return isCancelled;
            }
        
            @Override
            public boolean isDone() {
                return isDone;
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
                    if (!isRealDone){
                        if (isCancelled){
                            throw new CancellationException();
                        }

                        else if(executionException != null){
                            throw new ExecutionException(Task.this.executionException);
                        }

                        else if (Thread.currentThread().isInterrupted()){
                            throw new InterruptedException();
                        }

                        else if(cond.await(timeout, unit) == false){
                            throw new TimeoutException();
                        }
                        
                    }
                }

                finally{
                    lock.unlock();
                }
                @SuppressWarnings("unchecked")
                E ret = (E)retVal;
                return ret;
                
            }
        
        }

    }

    
}



