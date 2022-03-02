package il.co.ilrd.hashmap;

import java.util.Comparator;
import java.util.Map;

public class Pair <K,V> implements Map.Entry<K,V>{
    private K key;
    private V value;

    private Pair(K key, V value){}

    public static <K,V> Pair<K,V> of(K key, V value){
        return null;
    }/* create new pair */

    public static <K,V> Pair<V,K> swap(Pair<K,V> pair){
        return null;
    }/* create new Pair */

    public static <T extends Comparable<T>> Pair<T,T> minMax(T[] array){
        return null;
    }/* create new Pair */

    public static <T> Pair<T,T> minMax(T[] array, Comparator<T> comp){
        return null;
    }/* create new Pair */

    public K setKey(K key){
        return null;
    }
    @Override
    public K getKey() {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public V getValue() {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public V setValue(V value) {
        // TODO Auto-generated method stub
        return null;
    }
    @Override
    public int hashCode() {
        // TODO Auto-generated method stub
        return super.hashCode();
    }
    @Override
    public boolean equals(Object obj){
        return false;
    }
    @Override
    public String toString() {
        // TODO Auto-generated method stub
        return super.toString();
    }
    
}
