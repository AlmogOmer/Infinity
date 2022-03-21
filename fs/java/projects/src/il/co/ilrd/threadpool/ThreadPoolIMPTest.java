package il.co.ilrd.threadpool;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.CancellationException;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

import il.co.ilrd.threadpool.ThreadPoolIMP.Priority;

public class ThreadPoolIMPTest {
    public static void main(String[] args) {
        //test1();
        //test2();
        test3();
        //test4();

    }

    public static void test1(){
        System.out.println("**********Test1*********");
        ThreadPoolIMP threadPool = new ThreadPoolIMP(1);
        Callable<String> Task = new Callable<String>() {

            @Override
            public String call() {
                try {
                    Thread.sleep(10000);
                } catch (InterruptedException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
                return "Task 1";
            }

        };

        Future<String> future = threadPool.submit(Task);
        future.cancel(true);

        try {
            System.err.println("future.get() = " + future.get());
        } catch (InterruptedException | ExecutionException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }


    public static void test2(){
        System.out.println("**********Test2*********");
        ThreadPoolIMP tp = new ThreadPoolIMP(1);
        List<Future<Integer>> res = new ArrayList<>();


        //runnable
        Runnable testExecute = () -> { System.out.println("test Execute"); };
        Runnable testRunnable = () -> { System.out.println("test Runnable"); };
        Runnable testRunnablePriority1 = () -> { System.out.println("test Runnable p1"); };
        Runnable testRunnablePriority2 = () -> { System.out.println("test Runnable p2" ); };
        Runnable testRunnablePriority3 = () -> { System.out.println("test Runnable p3"); };

        //test execute, test submit(runnable) + priority
        tp.execute(testExecute); // MEDUIM
        tp.submit(testRunnable); // MEDUIM
        tp.submit(testRunnablePriority1, Priority.LOW);
        tp.submit(testRunnablePriority2, Priority.MEDIUM);
        tp.submit(testRunnablePriority3, Priority.HIGH);
        
        class Task implements Callable<Integer>{
            private Integer num;

            public Task(Integer num){
                this.num = num;
            }

            @Override
            public Integer call() throws Exception {
                System.out.println(num * 10);
                return num * 10;
            }

        }


        // test submit(callable) - no priority
        for(int i = 0; i < 5; ++i){
            Task testCallTask = new Task(i);
            res.add(tp.submit(testCallTask));
        }

        for (Future<Integer> future : res) {
            try{
                System.out.println(future.get());
            } catch (ExecutionException ex){
                ex.printStackTrace();
            } catch (InterruptedException ex) {
                ex.printStackTrace();
            }
        }


        Task testCallTaskP1 = new Task(10);
        Task testCallTaskP2 = new Task(20);
        Task testCallTaskP3 = new Task(30);

        tp.submit(testCallTaskP1, Priority.LOW);
        tp.submit(testCallTaskP2, Priority.MEDIUM);
        tp.submit(testCallTaskP3, Priority.HIGH);
    }

    public static void test3(){
        System.out.println("**********Test3*********");
        ThreadPoolIMP threadPool = new ThreadPoolIMP(3);
        List<Callable<String>> callables = new ArrayList<Callable<String>>();
        List<Future<String>> futures = new ArrayList<>();
        
        for (int i = 0; i < 10; ++i){
            callables.add(new Callable<String>() {
                public String call() throws Exception {
                    Thread.sleep(1000);
                    return "Task";
                }
            });
        }

        for(Callable<String> call : callables){
            futures.add(threadPool.submit(call));
        }

        //System.out.println("cancled? : " + futures.get(9).cancel(true));

        for(Future<String> future : futures){
            try {
                try {
                    System.out.println("future.get = " + future.get(5, TimeUnit.SECONDS));
                } catch (TimeoutException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            } catch (InterruptedException | ExecutionException e) {

                e.printStackTrace();
            }
        }
    }

    public static void test4(){
        System.out.println("**********Test4*********");
        ThreadPoolIMP threadPool = new ThreadPoolIMP(1);

        //callable
        class TaskCancle implements Callable<Integer>{

            @Override
            public Integer call() throws InterruptedException  {
                System.out.println("start");
                
                Thread.sleep(5000);
                
                System.out.println("stop");
                return 100;
            }
        }

        // test cancle, isCancle, isDone
        Future<Integer> fCancle = threadPool.submit(new TaskCancle());

        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        fCancle.cancel(true);

        System.out.println("cancle task is done? " + fCancle.isDone());
        System.out.println("cancle task is cancle? " + fCancle.isCancelled());

        try {
            System.out.println(fCancle.get());
        } catch (InterruptedException e) {
            System.out.println("can't get return value, thread interrupted");
        } catch (ExecutionException e) {
            System.out.println("can't get return value, task got exception");
        } catch (CancellationException e) {
            System.out.println("can't get return value, cancled");
        }
    }
    
}
