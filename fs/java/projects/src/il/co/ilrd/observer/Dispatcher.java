package il.co.ilrd.observer;

import java.util.ArrayList;
import java.util.Collection;

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
    }

    public void register(Callback<T> callback){
        callbackList.add(callback);
    }

    public void unregister(Callback<T> callback){
        callbackList.remove(callback);
    }
}
