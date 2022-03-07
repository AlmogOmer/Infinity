/*Reviewr: Yoni*/
package il.co.ilrd.hashmap;

import java.util.AbstractCollection;
import java.util.AbstractSet;
import java.util.ArrayList;
import java.util.Collection;
import java.util.ConcurrentModificationException;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.Set;

public class HashMap<K,V> implements Map<K,V>{
    private List<List<Pair<K,V>>> tableOfLists;
    private int capacity;
    private int mapVersionNum = 0;

    public HashMap(){
        this(16);
    }
    public HashMap(int capacity){
        if(capacity < 0){
            throw new IllegalArgumentException();
        }
        tableOfLists = new ArrayList<>(capacity);
        this.capacity = capacity;

        for (int i = 0; i < capacity; ++i) {
            tableOfLists.add(new LinkedList<>());
        }  
    }

    @Override
    public void clear() {
        ++mapVersionNum;
        for(List<Pair<K,V>> list : tableOfLists){
            list.clear();
        }   
    }

    @Override
    public boolean containsKey(Object key) {
        Objects.requireNonNull(key);

        int idx = key.hashCode() % capacity;
        if(tableOfLists.get(idx) == null){
            return false;
        }

        for(Pair<K,V> pair : tableOfLists.get(idx)){
            if(pair.getKey().equals(key)){
                return true;
            }
        }
        return false;
    }
    @Override
    public boolean containsValue(Object value) { 
        Collection<V> vals = values();
        return vals.contains(value);
    }

    @Override
    public V get(Object key) {
        Objects.requireNonNull(key);

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
        Objects.requireNonNull(arg0);

        ++mapVersionNum;
        int idx = arg0.hashCode() % capacity;
        for(Pair<K,V> pair :tableOfLists.get(idx)){
            if(pair.getKey().equals(arg0)){
                V oldValue =  pair.getValue();
                pair.setValue(arg1); 
                return oldValue;  
            }
        }

        tableOfLists.get(idx).add(Pair.of(arg0, arg1));
        return null;
    }
    @Override
    public void putAll(Map<? extends K, ? extends V> m) { 
        Objects.requireNonNull(m);

        ++mapVersionNum;
        for (Entry<? extends K, ? extends V> element : m.entrySet()) {
            put(element.getKey(), element.getValue());
        }

    }

    @Override
    public V remove(Object key) {
        Objects.requireNonNull(key);
        
        ++mapVersionNum;
        int idx = key.hashCode() % capacity;
        for(Pair<K,V> pair :tableOfLists.get(idx)){
            if(pair.getKey().equals(key)){
                V oldValue = pair.getValue();
                tableOfLists.get(idx).remove(pair);
                return oldValue;
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
        return new SetOfKey();
    }

    @Override
    public Collection<V> values() { 
        return new CollectionOfValue();
    }

    @Override
    public Set<Entry<K, V>> entrySet() { 
        return new SetOfPairs();
    }

    private class SetOfPairs extends AbstractSet<Entry<K,V>>{
        
        @Override
        public Iterator<Entry<K,V>> iterator() {
            return new SetOfPairsIter();
        }

        @Override
        public int size() {
            return HashMap.this.size();
        }

        private class SetOfPairsIter implements Iterator<Entry<K,V>>{
            private int iterVersionNum;
            private Iterator<List<Pair<K,V>>> outIter;
            private Iterator<Pair<K,V>> innerIter; 

            // Constructor
            private SetOfPairsIter(){
                iterVersionNum = mapVersionNum;

                outIter = tableOfLists.iterator();
                innerIter = outIter.next().iterator();
                findNextValid();
            }
            
            @Override
            public boolean hasNext() {
                return innerIter.hasNext(); 
            }

            @Override
            public Entry<K,V> next() {
                if (iterVersionNum != mapVersionNum){
                    throw new ConcurrentModificationException();
                }
                Entry<K,V> curr = innerIter.next();
                findNextValid();

                return curr;
            }

            private void findNextValid(){
                if (!innerIter.hasNext()) {
                    while(outIter.hasNext()){
                        List<Pair<K,V>> list = outIter.next();
                        if(!list.isEmpty()){
                            innerIter = list.iterator();
                            break;
                        }
                    }
                }
            }

        }
    }
    private class SetOfKey extends AbstractSet<K>{

        @Override
        public Iterator<K> iterator() {
            return new SetOfKeyIter();
        }

        @Override
        public int size() {
            return HashMap.this.size();
        }
        private class SetOfKeyIter implements Iterator<K>{
            private Iterator<Entry<K, V>> setPairsIter;

            private SetOfKeyIter() {
            	setPairsIter = new SetOfPairs().iterator();
            }

            @Override
            public boolean hasNext() {
                return setPairsIter.hasNext();
            }

            @Override
            public K next() {
                return setPairsIter.next().getKey();
            }

        }
    }
    private class CollectionOfValue extends AbstractCollection<V>{

        @Override
        public Iterator<V> iterator() {
            return new CollectionOfValueIter();
        }

        @Override
        public int size() {
            return HashMap.this.size();
        }

        private class CollectionOfValueIter implements Iterator<V>{
            private Iterator<Entry<K, V>> setPairsIter;

            private CollectionOfValueIter() {
            	setPairsIter = new SetOfPairs().iterator();
            }

            @Override
            public boolean hasNext() {
                return setPairsIter.hasNext();
            }

            @Override
            public V next() {
                return setPairsIter.next().getValue();
            }

        }

    }
    
}


