package il.co.ilrd.linked_list;

public class LinkedList {
    private Node head; 
 
    private static class Node {
        private Object data;
        private Node next;
 
        // Constructor
        private Node(Object data, Node next){
            this.data = data;
            this.next = next;
        }
    }

    private class IterList implements Iter{
        
        private Node node;
        
        // Constructor
        private IterList(Node node){
            this.node = node;
        }
        
        @Override
        public Object Next(){
            Object nodeData = this.node.data;
            node = node.next;

            return nodeData;
        }

        @Override
        public boolean HasNext(){
            return null != this.node;
        }

    }
    
    public void PushFront(Object data){

        Node newNode = new Node(data, head);
        this.head = newNode;
    }

    public Object PopFront(){
        
        if (IsEmpty())
        {
            return null;
        }

        Object popped = head.data;
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
        Iter runner = Begin();
        while(runner.HasNext())
        {
            ++counter;
            runner.Next();
        }

        return counter;
    }

    public Iter Find(Object data){
        if (IsEmpty())
        {
            return null;
        }
        
        Iter runner = Begin();
        Iter returnRunner = Begin();

        while(runner.HasNext() && !runner.Next().equals(data))
        {
            returnRunner.Next();
        }

        return returnRunner;
    }

    public Iter Begin(){
        if (IsEmpty())
        {
            return null;
        }

        Iter begin = new IterList(this.head);
        return begin;
    }

}


