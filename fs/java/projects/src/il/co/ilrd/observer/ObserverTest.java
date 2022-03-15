/*Reviewer : Ofek*/

package il.co.ilrd.observer;
import java.util.function.Consumer;
public class ObserverTest{
    public static void main(String[] args) {
        Subject magazin = new Subject();
        Observer1 reader = new Observer1();
        Observer2 reader2 = new Observer2();
        reader.register(magazin);
        reader2.register(magazin);
        System.out.println("current magazin price: " + magazin.getData()); 
        magazin.setData(15);
        System.out.println("current magazin price: " + magazin.getData()); 
        System.out.println("current magazin price appears in reader: " + reader.getData()); 
        System.out.println("current magazin price appears in reader2: " + reader2.getData()); 
        reader.unregister();
        magazin.setData(17);
        reader.register(magazin);
        Consumer<Integer> newupdate = new Consumer<Integer>() {
            @Override
            public void accept(Integer t) {
                reader2.setData(t);
                System.out.println("obs1 Got the notify in a new way: " + t);
            }
        };
    
        Runnable newstopService = new Runnable() {
            @Override
            public void run() {
                System.out.println("obs1 stopping the service in a new way");
            }
        };
        reader2.setUpdate(newupdate);
        reader2.setStopService(newstopService);

        magazin.setData(20);
        magazin.stopService();
    }
}

class Subject{
    private Dispatcher<Integer> dispatcher = new Dispatcher<> ();
    private Integer subData = 10;

    public void setData(Integer subData){
        this.subData = subData;
        dispatcher.notifyAllCallback(subData);
    }

    public Integer getData(){
        return subData;
    }
    
    public void register(Callback<Integer> callback){
        System.out.println("thanks for registering!");
        dispatcher.register(callback);
    }

    public void stopService(){
        System.out.println("we are not exist anymore");
        dispatcher.stopAllCallback();
    }

}

class Observer1{
    private  Callback <Integer> mycall1;
    private Integer obs1Data = 0;

    Consumer<Integer> myupdate1 = new Consumer<Integer>() {
        @Override
        public void accept(Integer t) {
            obs1Data = t;
            System.out.println("obs1 Got the notify: " + t);
        }
    };

    Runnable mystopService1 = new Runnable() {
        @Override
        public void run() {
            System.out.println("obs1 stopping the service");
        }
    };

    public Observer1(){
        mycall1 = new Callback <>(myupdate1,mystopService1);
    }

    public void register(Subject subject){
        subject.register(mycall1);
    }

    public Integer getData(){
        return obs1Data;
    }

    public void setData(Integer obs1Data){
        this.obs1Data = obs1Data;
    }

    public void unregister(){
        mycall1.unregister();
    }

    public void setUpdate(Consumer<Integer> update){
        mycall1.setUpdate(update);
    }
    
    public void setStopService(Runnable stopService){
        mycall1.setStopService(stopService);
    }

}

class Observer2{
    private  Callback <Integer> mycall2;
    private Integer obs2Data = 0;

    Consumer<Integer> myupdate2 = new Consumer<Integer>() {
        @Override
        public void accept(Integer t) {
            obs2Data = t;
            System.out.println("obs2 Got the notify: " + t);
        }
    };

    Runnable mystopService2 = new Runnable() {
        @Override
        public void run() {
            System.out.println("obs2 stopping the service");
        }
    };

    public Observer2(){
        mycall2 = new Callback <>(myupdate2,mystopService2);
    }

    public void register(Subject subject){
        subject.register(mycall2);
    }

    public Integer getData(){
        return obs2Data;
    }

    public void setData(Integer obs2Data){
        this.obs2Data = obs2Data;
    }

    public void unregister(){
        mycall2.unregister();
    }

    public void setUpdate(Consumer<Integer> update){
        mycall2.setUpdate(update);
    }
    
    public void setStopService(Runnable stopService){
        mycall2.setStopService(stopService);
    }
}