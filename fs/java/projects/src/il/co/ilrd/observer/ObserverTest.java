/*Reviewer : Ofek*/
package il.co.ilrd.observer;
import java.util.function.Consumer;

public class ObserverTest{
    public static void main(String[] args) {
        Subject magazin = new Subject();
        Observer reader = new Observer();
        Observer reader2 = new Observer();
        reader.register(magazin);
        reader2.register(magazin);
        Consumer<Integer> newupdate = new Consumer<Integer>() {
            @Override
            public void accept(Integer t) {
                reader2.setData(t);
                System.out.println("obs2 Got the notify: " + t);
            }
        };
    
        Runnable newstopService = new Runnable() {
            @Override
            public void run() {
                System.out.println("obs2 stopping the service");
            }
        };
        reader2.setUpdate(newupdate);
        reader2.setStopService(newstopService);
        System.out.println("current magazin price: " + magazin.getData()); 
        magazin.setData(15);
        System.out.println("current magazin price: " + magazin.getData()); 
        System.out.println("current magazin price appears in reader: " + reader.getData()); 
        System.out.println("current magazin price appears in reader2: " + reader2.getData()); 
        reader.unregister();
        magazin.setData(17);
        reader.register(magazin);
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

class Observer{
    private  Callback <Integer> mycall;
    private Integer obsData = 0;

    Consumer<Integer> myupdate = new Consumer<Integer>() {
        @Override
        public void accept(Integer t) {
            obsData = t;
            System.out.println("obs Got the notify: " + t);
        }
    };

    Runnable mystopService = new Runnable() {
        @Override
        public void run() {
            System.out.println("obs stopping the service");
        }
    };

    public Observer(){
        mycall = new Callback <>(myupdate,mystopService);
    }

    public void register(Subject subject){
        subject.register(mycall);
    }

    public Integer getData(){
        return obsData;
    }

    public void setData(Integer obsData){
        this.obsData = obsData;
    }

    public void unregister(){
        mycall.unregister();
    }

    public void setUpdate(Consumer<Integer> update){
        mycall.setUpdate(update);
    }
    
    public void setStopService(Runnable stopService){
        mycall.setStopService(stopService);
    }

}

