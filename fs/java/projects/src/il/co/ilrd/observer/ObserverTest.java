package il.co.ilrd.observer;

import java.util.function.Consumer;
public class ObserverTest{
    public static void main(String[] args) {
        Subject magazin = new Subject();
        Observer reader = new Observer();
        reader.register(magazin);
        System.out.println("current magazin price: " + magazin.getData()); 
        magazin.setData(15);
        System.out.println("current magazin price: " + magazin.getData()); 
        System.out.println("current magazin price appears in reader: " + reader.getData()); 
        reader.mycall.unregister();
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
    public  Callback <Integer> mycall;
    private Integer obsData = 0;

    Consumer<Integer> myupdate = new Consumer<Integer>() {
        @Override
        public void accept(Integer t) {
            obsData = t;
            System.out.println("Got the notify: " + t);
        }
    };

    Runnable mystopService = new Runnable() {
        @Override
        public void run() {
            System.out.println("stopping the service");
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
}
