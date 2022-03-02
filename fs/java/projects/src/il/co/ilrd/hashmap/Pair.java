/*Reviewer : Naama*/

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
        return Pair.of(pair.getValue(),pair.getKey());
    }

    public static <T extends Comparable<T>> Pair<T,T> minMax(T[] array){
        Comparator<T> comp = new Comparator<T>() {
			
			@Override
			public int compare(T obj1, T obj2) {
				return obj1.compareTo(obj2);
			}
		};
		
		return minMax(array, comp);
    }

    public static <T> Pair<T,T> minMax(T[] array, Comparator<T> comp){
        int i = 1;
        T min = array[0];
        T max = array[0];
        int size = array.length;
        if (size == 0) {
			return null;
		}
        if (size % 2 == 0) {
            if ( 0 < comp.compare(array[0],array[1])){
                max = array[0];
                min = array[1];
            } else {
                min = array[0];
                max = array[1];
            }
            i = 2;
        } 
 
        while (i < size - 1) {
            if (0 < comp.compare(array[i],array[i + 1])) {
                if (0 < comp.compare(array[i],max)) {
                    max = array[i];
                }
                if (0 > comp.compare(array[i + 1],min)) {
                    min = array[i + 1];
                }
            } else {
                if (0 < comp.compare(array[i + 1],max)) {
                    max = array[i + 1];
                }
                if (0 > comp.compare(array[i],min)) {
                    min = array[i];
                }
            }
            i += 2;
        }

        return Pair.of(min, max) ;
    
    }

    public K setKey(K key){
        K old_key = this.key;
        this.key = key;
        return old_key;
    }
    @Override
    public K getKey() {
        return key;
    }

    @Override
    public V getValue() {
        return value;
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
