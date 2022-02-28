package il.co.ilrd.genericlist;

import java.util.ConcurrentModificationException;
import java.util.Iterator;

public class GenericList<E> implements Iterable<E> {
    private Node<E> head; 
    private int versionNum = 0;
 
    private static class Node<T> {
        private T data;
        private Node<T> next;
 
        // Constructor
        private Node(T data, Node<T> next){
            this.data = data;
            this.next = next;
        }
    }

    @Override
    public Iterator<E> iterator() {
        Iterator<E> iter = new ListIter(this.head);
        return iter;
    }

    private class ListIter implements Iterator<E>{
        private Node<E> node;
        private int iterVersionNum;

        // Constructor
        private ListIter(Node<E> node){
            this.node = node;
            iterVersionNum = versionNum;
        }

        @Override
        public boolean hasNext() {
            if(iterVersionNum != versionNum){
                throw new ConcurrentModificationException();
            }

            return null != this.node;
        }

        @Override
        public E next(){
            if(iterVersionNum != versionNum){
                throw new ConcurrentModificationException();
            }
            E nodeData = this.node.data;
            node = node.next;

            return nodeData;
        }

    }
    
    public void PushFront(E data){
        ++versionNum;
        Node<E> newNode = new Node<E>(data, head);
        this.head = newNode;
    }

    public E PopFront(){
        if (IsEmpty())
        {
            return null;
        }

        ++versionNum;
        E popped = head.data;
        this.head = head.next;

        return popped;
    }

    public boolean IsEmpty(){
        return this.head == null;
    }

    public int Size(){
        if (IsEmpty())
        {
            return 0;
        }
        int counter = 0;
        Iterator<E> runner = iterator();
        while(runner.hasNext())
        {
            ++counter;
            runner.next();
        }

        return counter;
    }

    public Iterator<E> Find(E data){
        if (IsEmpty())
        {
            return null;
        }
        
        Iterator<E> runner = iterator();
        Iterator<E> returnRunner = iterator();

        while(runner.hasNext() && !runner.next().equals(data))
        {
            returnRunner.next();
        }

        return returnRunner;
    }

    public static <E> GenericList<E> reversList(GenericList <E> list){
        GenericList<E> reversedList = new GenericList<E>();
        Iterator<E> runner = list.iterator();
    
        while(runner.hasNext())
        {
            reversedList.PushFront(runner.next());
        }
    
        return reversedList;
    }
    public static <E> GenericList<E> merge(GenericList <E> list1, GenericList <E> list2){
        GenericList<E> mergeList = new GenericList<E>();
        Iterator<E> runner1 = list1.iterator();
        Iterator<E> runner2 = list2.iterator();

        while(runner1.hasNext())
        {
            mergeList.PushFront(runner1.next());
        }

        while(runner2.hasNext())
        {
            mergeList.PushFront(runner2.next());
        }

        return reversList(mergeList);
    }

}
