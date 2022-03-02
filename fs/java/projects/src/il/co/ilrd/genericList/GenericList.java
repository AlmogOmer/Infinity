/*reviewer : Shani*/

package il.co.ilrd.genericList;

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
        return (Iterator<E>) new ListIter(head);
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
    
    public void pushFront(E data){
        ++versionNum;
        head = new Node<E>(data, head);
    }

    public E popFront(){
        if (isEmpty())
        {
            return null;
        }

        ++versionNum;
        E popped = head.data;
        head = head.next;

        return popped;
    }

    public boolean isEmpty(){
        return head == null;
    }

    public int size(){
        int counter = 0;
        for(E element : this)
        {
            ++counter;
        }

        return counter;
    }

    public Iterator<E> find(E data){      
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
        
        for(E element : list)
        {
            reversedList.pushFront(element);
        }

        return reversedList;
    }
    public static <E> GenericList<E> merge(GenericList <E> list1, GenericList <E> list2){
        GenericList<E> mergeList = new GenericList<E>();

        for(E element : list1)
        {
            mergeList.pushFront(element);
        }

        for(E element : list2)
        {
            mergeList.pushFront(element);
        }

        return mergeList;
    }

}



