package il.co.ilrd.executor;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.ScheduledFuture;
import java.util.concurrent.TimeUnit;

public class ExecutorExercise {
    public static void executor1() {
        ExecutorService e = Executors.newSingleThreadExecutor();
        Callable<String> Task = new Callable<String>() {

            @Override
            public String call() throws Exception {
                return "Task 1";
            }

        };

        Future<String> future = e.submit(Task);
        try {
            System.out.println("future.get() = " + future.get());
        } catch (InterruptedException | ExecutionException e1) {
            e1.printStackTrace();
        }
        e.shutdown();
    }

    public static void SinglePool() {
        ExecutorService e1 = Executors.newSingleThreadExecutor();
        Test(e1,  "SinglePool : ");
    }

    public static void FixedPool() {
        ExecutorService e1 = Executors.newFixedThreadPool(3);
        Test(e1,  "FixedPool : ");
    }

    public static void CachedPool() {
        ExecutorService e1 = Executors.newCachedThreadPool();
        Test(e1,  "CachedPool : ");
    }

    public static void Test(ExecutorService e1,  String name){
        List<Callable<String>> callables = new ArrayList<Callable<String>>();
        List<Future<String>> futures = new ArrayList<>();

        for (int i = 0; i < 5; ++i){
            callables.add(new Callable<String>() {
                public String call() throws Exception {
                    return "Task";
                }
            });
        }
        
        long start = System.nanoTime(); 
        
        try {
            futures = e1.invokeAll(callables);
        } catch (InterruptedException e2) {
            e2.printStackTrace();
        }

        for(Future<String> future : futures){
            try {
                System.out.println("future.get = " + future.get());
            } catch (InterruptedException | ExecutionException e) {

                e.printStackTrace();
            }
        }
        
        e1.shutdown();
        long end = System.nanoTime(); 
        System.out.println(name + (end-start));
    }
    
    public static void SchedualedPool() {
        ScheduledExecutorService e1 = Executors.newSingleThreadScheduledExecutor();
        List<Callable<String>> callables = new ArrayList<Callable<String>>();
        List<Future<String>> futures = new ArrayList<>();
        for (int i = 0; i < 5; ++i){
            callables.add(new Callable<String>() {
                public String call() throws Exception {
                    return "Task";
                }
            });
        }
        long start = System.nanoTime(); 
        
        for(Callable<String> call : callables){
            futures.add(e1.schedule(call, 2, TimeUnit.SECONDS));
        }

        for(Future<String> future : futures){
            try {
                System.out.println("future.get = " + future.get());
            } catch (InterruptedException | ExecutionException e) {

                e.printStackTrace();
            }
        }
        
        e1.shutdown();

        long end = System.nanoTime(); 
        System.out.println("SchedualedPool : " + (end-start));
    }

    public static void SchedualedPool1() {
        ScheduledExecutorService scheduler = Executors.newSingleThreadScheduledExecutor();
        Runnable beeper = new Runnable() {
            public void run() { System.out.println("beep"); }
          };
        
        ScheduledFuture<?> beeperHandle = scheduler.scheduleAtFixedRate(beeper, 1, 1, TimeUnit.SECONDS);

        /*scheduler.schedule(new Runnable() {
            public void run() { beeperHandle.cancel(true); }}, 10, TimeUnit.SECONDS);*/

        try {
            Thread.sleep(10000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        scheduler.shutdown();
    }


    public static void main(String[] args) {
        executor1();
        SinglePool();
        FixedPool();
        CachedPool();
        SchedualedPool();
        SchedualedPool1();

    }


}
