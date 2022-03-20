package il.co.ilrd.threadpool;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Executor;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;
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
            new Thread(runnable).start();
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


    private class ThreadImp implements Runnable{

        @Override
        public void run() {
            while(true){
                Task<?> task = tasks.dequeue();
                task.currThread = Thread.currentThread();
                task.runTask();
            }
            
        }
        
    }

    private class Task<T> implements Comparable<Task<T>>{
        private final Callable<T> task;
        private final int priority;
        private Thread currThread;
        private final TaskFuture<T> taskFuture;

        public Task(Callable<T> task, int priority){
           this.task = task;
           this.priority = priority;
           taskFuture = new TaskFuture<T>();
        }

        public void runTask(){
            while(!taskFuture.isCancelled())
            {  
                try {
                    taskFuture.retVal = task.call();
                } catch (Exception e) {
                    e.printStackTrace();
                }

            }

        }
        
        public Future<T> getFuture(){
            return taskFuture;
        }

        @Override
        public int compareTo(Task<T> other) {
            return (this.priority - other.priority);
        }

        private class TaskFuture<E> implements Future<E>{
            private T retVal = null;
            private boolean isCancelled = false;
        
            @Override
            public boolean cancel(boolean mayInterruptIfRunning) {
                if(!isDone() && !isCancelled() && mayInterruptIfRunning){
                    Task.this.currThread.interrupt();
                    isCancelled = true;
                    return true;
                }
                return false;
            }
        
            @Override
            public boolean isCancelled() {
                return isCancelled;
            }
        
            @Override
            public boolean isDone() {
                return (retVal != null);
            }
        
            @Override
            public E get() throws InterruptedException, ExecutionException {
                // TODO Auto-generated method stub
                return null;
            }
        
            @Override
            public E get(long timeout, TimeUnit unit) throws InterruptedException, ExecutionException, TimeoutException {
                // TODO Auto-generated method stub
                return null;
            }
        
        }

    }

    
}



