/*Reviewer : Ofek*/
package il.co.ilrd.observer;
import java.util.Objects;
import java.util.function.Consumer;

public class Callback <T>{

    private Dispatcher<T> dispatcher;
    private Consumer<T> update;
    private Runnable stopService;

    public Callback(Consumer<T> update, Runnable stopService){
        Objects.requireNonNull(update);
        Objects.requireNonNull(stopService);
        
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
        Objects.requireNonNull(dispatcher);
        stopService.run();
        dispatcher.unregister(this);
        dispatcher = null;
    }

    public void setUpdate(Consumer<T> update){
        Objects.requireNonNull(update);
        this.update = update;
    }
    
    public void setStopService(Runnable stopService){
        Objects.requireNonNull(stopService);
        this.stopService = stopService;
    }
}