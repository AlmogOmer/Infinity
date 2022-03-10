package il.co.ilrd.factory;

import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;

public class Factory<T, D, K> {
    private Map<K, Function<D, ? extends T>> factoryMap = new HashMap<>();

    public void add(K key, Function<D, ? extends T> func) {
        factoryMap.put(key, func);
    }

    public T create(K key) {
        if (!factoryMap.containsKey(key)){
            throw new IllegalArgumentException();
        }
        return factoryMap.get(key).apply(null);
    }

    public T create(K key, D data) {
        if (!factoryMap.containsKey(key)){
            throw new IllegalArgumentException();
        }
        return factoryMap.get(key).apply(data);
    }
    
}

