/*Reviwer : Ofek*/
package il.co.ilrd.factory;

import java.util.HashMap;
import java.util.Map;
import java.util.Objects;
import java.util.function.Function;

public class Factory<T, D, K> {
    private Map<K, Function<D, ? extends T>> factoryMap = new HashMap<>();

    
    public void add(K key, Function<D, ? extends T> func) { //can contain only one key null  
        Objects.requireNonNull(func);
        factoryMap.put(key, func);
    }

    public T create(K key) {
        return create(key, null);
    }

    public T create(K key, D data) {
        if (!factoryMap.containsKey(key)){
            throw new IllegalArgumentException();
        }
        return factoryMap.get(key).apply(data);
    }
    
}

