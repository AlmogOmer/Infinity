package il.co.ilrd.hashmap;

import java.util.Comparator;
import java.util.Map;

public class Pair <K,V> implements Map.Entry<K,V>{
    private K key;
    private V value;

    private Pair(K key, V value){
        this.key = key;
        this.value = value;
    }

    public static <K,V> Pair<K,V> of(K key, V value){
        return new Pair<K,V>(key,value);
    }

    public static <K,V> Pair<V,K> swap(Pair<K,V> pair){
        return new Pair<V,K>(pair.value,pair.key);
    }

    public static <T extends Comparable<T>> Pair<T,T> minMax(T[] array){
        return null;
    }/* create new Pair */

    public static <T> Pair<T,T> minMax(T[] array, Comparator<T> comp){
        return null;
    }/* create new Pair */

    public K setKey(K key){
        K old_key = this.key;
        this.key = key;
        return old_key;
    }
    @Override
    public K getKey() {
        return this.key;
    }

    @Override
    public V getValue() {
        return this.value;
    }

    @Override
    public V setValue(V value) {
        V old_value = this.value;
        this.value = value;
        return old_value;
    }
    @Override
    public int hashCode() {
        
        return this.key.hashCode() + this.value.hashCode();
    }
    @Override
    public boolean equals(Object obj){
        if (obj instanceof Pair) {
            Pair<K,V> pair = (Pair<K,V>)obj;
            return (
                this.key == pair.key &&
                this.value == pair.value
            );
        }
        return false;
    }

    @Override
    public String toString() {
        return "(" + key + "," + value + ")";
    }
    
}
