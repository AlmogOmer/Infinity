
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
            Object nodeData = this.node.data;
            if(this.HasNext())
            {
                this.node = this.node.next;
            }

            return nodeData;
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
        Iter runner = new IterList(this.head);
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
        
        IterList runner = new IterList(this.head);

        while(runner.HasNext())
        {
            if(runner.node.data == data)
            {
                return (Iter)runner;
            }
            runner.Next();
        }

        if(runner.node.data == data)
        {
            return (Iter)runner;
        }

        return null;

    }

    public Iter Begin(){
        Iter begin = new IterList(this.head);
        return begin;
    }

}


