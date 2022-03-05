package il.co.ilrd.hashmap;

import java.util.AbstractCollection;
import java.util.AbstractSet;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class HashMap<K,V> implements Map<K,V>{
    private List<List<Pair<K,V>>> tableOfLists;
    private int capacity;

    public HashMap(){
        this(16);
    }
    public HashMap(int capacity){
        tableOfLists = new ArrayList<>(capacity);
        this.capacity = capacity;

        for (int i = 0; i < capacity; ++i) {
            tableOfLists.add(new LinkedList<>());
        }  
    }
    
    @Override
    public void clear() {
        for(List<Pair<K,V>> list : tableOfLists){
            list.clear();
        }   
    }

    @Override
    public boolean containsKey(Object key) {
        int idx = key.hashCode() % capacity;
        if(tableOfLists.get(idx) == null){
            return false;
        }

        for(List<Pair<K,V>> list : tableOfLists){
            for(Pair<K,V> pair : list){
                if(pair.getKey().equals(key)){
                    return true;
                }
            }
        }  
        return false;
    }
    @Override
    public boolean containsValue(Object value) { 
        for(List<Pair<K,V>> list : tableOfLists){
            for(Pair<K,V> pair : list){
                if(pair.getValue().equals(value)){
                    return true;
                }
            }
        }  
        return false;
    }

    @Override
    public V get(Object key) {
        int idx = key.hashCode() % capacity;
        for(Pair<K,V> pair :tableOfLists.get(idx)){
            if(pair.getKey().equals(key)){
                return pair.getValue();
            }
        }

        return null;
    }
    @Override
    public boolean isEmpty() {
        for(List<Pair<K,V>> list : tableOfLists){
            if(!list.isEmpty()){
                return false;
            }
        }
        return true;
    }
 
    @Override
    public V put(K arg0, V arg1) {
        int idx = arg0.hashCode() % capacity;
        if (tableOfLists.get(idx) != null){
            for(Pair<K,V> pair :tableOfLists.get(idx)){
                if(pair.getKey().equals(arg0)){
                    V oldValue =  pair.getValue();
                    pair.setValue(arg1); 
                    return oldValue;  
                }
            }
        }

        tableOfLists.get(idx).add(Pair.of(arg0, arg1));
        return null;
    }
    @Override
    public void putAll(Map<? extends K, ? extends V> m) { 
    }

    @Override
    public V remove(Object key) {
        int idx = key.hashCode() % capacity;
        if (tableOfLists.get(idx) != null){
            for(Pair<K,V> pair :tableOfLists.get(idx)){
                if(pair.getKey().equals(key)){
                    V oldValue = pair.getValue();
                    tableOfLists.get(idx).remove(pair);
                    return oldValue;
                }
            }
        }
        return null;
    }

    @Override
    public int size() {
        int counter = 0;
        for(List<Pair<K,V>> list : tableOfLists){
            counter += list.size();
        }
        return counter;
    }

    @Override
    public Set<K> keySet() { 
        // return a set of the keys, with iterator
        return null;
    }

    @Override
    public Collection<V> values() { 
        // return collection of value
        return null;
    }

    @Override
    public Set<Entry<K, V>> entrySet() { 
        // return reflection of the map, without duplicate
        // set is iterabl
        return null;
    }

    private class SetOfPairs extends AbstractSet<Entry<K,V>>{
        private SetOfPairs(){}
        
        @Override
        public Iterator<Entry<K,V>> iterator() {
            // TODO Auto-generated method stub
            return null;
        }

        @Override
        public int size() {
            // TODO Auto-generated method stub
            return 0;
        }

        private class SetOfPairsIter implements Iterator<Entry<K,V>>{

            @Override
            public boolean hasNext() {
                // TODO Auto-generated method stub
                return false;
            }

            @Override
            public Entry<K,V> next() {
                // TODO Auto-generated method stub
                return null;
            }

        }
    }
    private class SetOfKey extends AbstractSet<K>{

        @Override
        public Iterator<K> iterator() {
            // TODO Auto-generated method stub
            return null;
        }

        @Override
        public int size() {
            // TODO Auto-generated method stub
            return 0;
        }
        private class SetOfKeyIter implements Iterator<K>{

            @Override
            public boolean hasNext() {
                // TODO Auto-generated method stub
                return false;
            }

            @Override
            public K next() {
                // TODO Auto-generated method stub
                return null;
            }

        }
    }
    private class CollectionOfValue extends AbstractCollection<V>{

        @Override
        public Iterator<V> iterator() {
            // TODO Auto-generated method stub
            return null;
        }

        @Override
        public int size() {
            // TODO Auto-generated method stub
            return 0;
        }
        private class CollectionOfValueIter implements Iterator<V>{

            @Override
            public boolean hasNext() {
                // TODO Auto-generated method stub
                return false;
            }

            @Override
            public V next() {
                // TODO Auto-generated method stub
                return null;
            }

        }

    }
    
}

