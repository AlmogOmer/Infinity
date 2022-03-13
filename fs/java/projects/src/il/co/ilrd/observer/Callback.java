package il.co.ilrd.observer;

import java.util.function.Consumer;

public class Callback <T>{

    private Dispatcher<T> dispatcher;
    private Consumer<T> update;
    private Runnable stopService;

    public Callback(Consumer<T> update, Runnable stopService){
        this.update = update;
        this.stopService = stopService;
    }
    
    public void update(T data){
        update.accept(data);
    }
    
    public void stopService(){
        stopService.run();
    }

    public void setDispatcher(Dispatcher<T> dispatcher){
        this.dispatcher = dispatcher;
    }

    public void unregister(){
        dispatcher.unregister(this);
    }

    public void setUpdate(Consumer<T> update){
        this.update = update;
    }
    
    public void setStopService(Runnable stopService){
        this.stopService = stopService;
    }
}