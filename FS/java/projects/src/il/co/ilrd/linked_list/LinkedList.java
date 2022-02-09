
public class LinkedList {
    private Node head; 
 
    private class Node {
        private Object data;
        private Node next;
 
        // Constructor
        private Node(Object newData, Node newNext){
            data = newData;
            next = newNext;
        }

    }

    private class IterList implements Iter{
        
        private Node node;
        
        // Constructor
        private IterList(Node newnode){
            node = newnode;
        }
        
        @Override
        public Object Next(){
            if(this.HasNext())
            {
                this.node = this.node.next;
                return this.node.data;
            }

            return null;

        }

        @Override
        public boolean HasNext(){
            return null != this.node.next;
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
        int counter = 1;
        Iter runner = new IterList(head);
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
        
        Iter runner = new IterList(head);
        if(this.head.data == data)
        {
            return runner;
        }

        while(runner.HasNext())
        {
            if(runner.Next() == data)
            {
                runner.Next();
                return runner;
            }
            runner.Next();
        }

        return null;

    }

    public Iter Begin(){
        Iter begin = new IterList(head);
        return begin;
    }

}


