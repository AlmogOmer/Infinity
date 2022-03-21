/*Reviewer : Ofek*/
package il.co.ilrd.threadpool;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.CancellationException;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Executor;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
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
    private List<ThreadImp> threads = new ArrayList<>();

    public ThreadPoolIMP(int numOfThreads){
        tasks = new WaitablePriorityQueueCond<>();

        for(int i=0; i<numOfThreads; i++){
            threads.add(new ThreadImp());
        }

        for(ThreadImp runnable : threads){
            runnable.thread.start();
        }
    }

    @Override
    public void execute(Runnable command) {
        Task<?> task = new Task<>(Executors.callable(command), 1);
        tasks.enqueue(task);  
    }

    private <T> Future<T> submitImp(Callable<T> callable, int priority){
        Task<T> task = new Task<>(callable, priority);
        tasks.enqueue(task); 
        return task.getFuture();
    }

    public <T> Future<T> submit(Callable<T> callable, Priority priority){
        return submitImp(callable, priority.ordinal());
    }
    
    public <T> Future<T> submit(Callable<T> callable){
        return submitImp(callable, 1);
    }

    public Future<Object> submit(Runnable runnable, Priority priority){
        return submitImp(Executors.callable(runnable), priority.ordinal());
    }
    public Future<Object> submit(Runnable runnable){
        return submitImp(Executors.callable(runnable), 1);
    }

    public <T> Future<T> submit(Runnable runnable, Priority priority, T result){
        return submitImp(Executors.callable(runnable, result), priority.ordinal());
    }

    private <T> boolean removeTask(Task<T> task){
        return tasks.remove(task);
    }


    private class ThreadImp implements Runnable{
        private Thread thread = new Thread(this);

        @Override
        public void run() {
            while(true){
                Task<?> task = tasks.dequeue();
                task.setcurrThread(thread);
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



