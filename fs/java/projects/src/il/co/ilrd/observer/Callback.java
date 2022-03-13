package il.co.ilrd.observer;

import java.util.function.Consumer;

public class Callback <T>{

    private Dispatcher<T> dispatcher;
    private Consumer<T> update;
    private Runnable stopService;

    public Callback(Consumer<T> update, Runnable stopService){}
    
    public void update(T data){}
    
    public void stopService(){}

    public void setDispatcher(Dispatcher<T> dispatcher){}

    public void unregister(){}

    public void setUpdate(Consumer<T> update){}
    
    public void setStopService(Runnable stopService){}
}