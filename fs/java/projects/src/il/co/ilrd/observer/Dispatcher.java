/*Reviewer : Ofek*/
package il.co.ilrd.observer;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Objects;

public class Dispatcher <T>{
    
    private Collection<Callback<T>> callbackList = new ArrayList<>();

    public void notifyAllCallback(T data){
        for(Callback<T> callback : callbackList){
            callback.update(data);
        }
    }
    
    public void stopAllCallback(){
        for(Callback<T> callback : callbackList){
            callback.stopService();
        }
        
        callbackList.clear();
    }

    public void register(Callback<T> callback){
        Objects.requireNonNull(callback);
        
        callbackList.add(callback);
        callback.setDispatcher(this);
    }

    public void unregister(Callback<T> callback){
        System.out.println("we are sorry that you are leaving");
        callbackList.remove(callback);
    }

}
