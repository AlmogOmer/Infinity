
//package il.co.ilrd.exam; 
import java.util.Arrays;
import java.util.ListIterator;
import java.util.Stack;

public class exam{

    public static void main(String[] args) {
        /*q1 e = new q1();
        e.setall(5);
        System.out.println("val in idx 4 : " + e.getVal(4));
        e.setVal(3, 1);
        System.out.println("val in idx 4 : " + e.getVal(4));
        System.out.println("val in idx 3 : " + e.getVal(3));
        try {
            Thread.sleep(2);
        } catch (InterruptedException e1) {
            e1.printStackTrace();
        }
        e.setall(8);
        System.out.println("val in idx 3 : " + e.getVal(3));*/
        
        /*int[] arr = {2,3,4,9,1,10,6,16,21,5};
        System.out.println(q2.sumInArray(arr,10,17));*/

        /*
        LinkedList list = new LinkedList();
        Integer x1 = 3;
        Integer x2 = 1;
        Integer x3 = 7;
        Integer x4 = 8;
        Integer x5 = 2;
        Integer x6 = 5;
        Integer x7 = 6;

        list.PushFront(x1);
        list.PushFront(x2);
        list.PushFront(x3);
        list.PushFront(x4);
        list.PushFront(x5);
        list.PushFront(x6);
        list.PushFront(x7);
        System.out.print("***before***");
        list.printList();
        list.pivotSort(6);
        System.out.print("***after***");
        list.printList();*/

        /*System.out.println(q8.mul(2, 3));
        System.out.println(q8.div(8, 4));
        System.out.println(q8.add1(9, 1));*/

        /*q6 stack = new q6();
        stack.stackPush(7);
        stack.stackPush(2);
        stack.stackPush(1);
        stack.stackPush(4);
        stack.stackPush(5);

        System.out.println(stack.getMin());
        stack.stackPop();
        System.out.println(stack.getMin());
        stack.stackPush(0);
        System.out.println(stack.getMin());
        stack.stackPop();
        stack.stackPush(19);
        stack.stackPush(8);
        System.out.println(stack.getMin());*/

        q7 par = new q7();
        System.out.println(par.balancedPar("{(2+5)-[(2-5)+(7+7)]}"));
        System.out.println(par.balancedPar("{)-[(2-5)+(7+7)]}"));

    }


}

class q1{
    public int[] array;
    private long[] timearray;
    private int allval;
    private long timeall;

    public q1(){
        this.array = new int[100];
        this.timearray = new long[100];
        this.allval = 0;
        this.allval = 0;
    }

    public void setVal(int idx, int val){
        array[idx] = val;
        timearray[idx] = System.currentTimeMillis();
    }

    public int getVal(int idx){
        if(timearray[idx] < timeall){
            return allval;
        }
    
        else{
            return array[idx];
        }
    }

    public void setall(int val){
        allval = val;
        timeall = System.currentTimeMillis();
    }
}

class q2{
    public static boolean sumInArray(int[] arr, int size, int sum){
        int start = 0;
        int end = size - 1;

        Arrays.sort(arr);
        while(end>start){
            if(arr[start] + arr[end] > sum){
                --end;
            }
            else if(arr[start] + arr[end] < sum){
                ++start;
            }
            else{
                return true;
            }
        }
        return false;
    }
}


interface Iter {
    public Object Next();
    public boolean HasNext();
  }

class LinkedList {
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

    public void Remove(Object data){
        
        Node temp = this.head;
        if (temp.data.equals(data)) {
            this.head = this.head.next;
        } else {
            while (temp.next != null) {
                if (temp.next.data.equals(data)) {
                    temp.next = temp.next.next;
                    break;
                } else {
                    temp = temp.next;
                }
            }
        }
    }

    public Iter Begin(){
        if (IsEmpty())
        {
            return null;
        }

        Iter begin = new IterList(this.head);
        return begin;
    }

    public void pivotSort(Object pivotData){
        IterList removed = (IterList)this.Find(pivotData);
        if(removed.node != null){
            this.Remove(pivotData);
            this.PushFront(pivotData);
        }

        Node curr = this.head;
        Node temp;
        while(curr != null){
            if((int)curr.data < (int)pivotData){
                temp = curr.next;
                this.Remove(curr.data);
                this.PushFront(curr.data);
                curr = temp;
            }
            else{
                curr = curr.next;
            }
        }

    }

    public void printList(){
        Node temp = head;
        System.out.print(temp.data + " ");
    
        while (temp.next != null){
            temp = temp.next;
            System.out.print(temp.data + " ");
        }
    }
}

class q8{
    public static int mul(int a, int b){
        if(b==0){
            return 0;
        }
        return (a+mul(a, --b));
    }

    public static int div(int a, int b){
        if(a<b){
            return 0;
        }
        return (1+div(a-b, b));
    }

    public static int add1(int x, int y){
       if(y == 0){
           return x;
       }
       
       return add1(x ^ y, (x & y) << 1); 
    }

}

class q6{
    Stack<Object>stack;
    Stack<Object>stackMin;

    public q6(){
        this.stack = new Stack();
        this.stackMin = new Stack();
    }

    public void stackPush(Object element){
        stack.push(element);
        if(stackMin.empty() || (int)element < (int)stackMin.peek()){
            stackMin.push(element);
        }
    }

    public void stackPop(){
        if(stackMin.peek().equals(stack.peek())){
            stackMin.pop();
        }
        stack.pop();
    }

    public Object getMin(){
        return stackMin.peek();
    }

}

class q7{
    Stack<Object>parStack;
    
    public q7(){
        this.parStack = new Stack();
    }

    public boolean balancedPar(String str){
        char[] array =  str.toCharArray();
        for(char ch: array){
            if(isOpenPar(ch)){
                this.parStack.push(ch);
            }
            else if(isClosePar(ch)){
                if(isCloseMatch((char)this.parStack.peek(), ch)){
                    this.parStack.pop();
                }
                else{
                    return false;
                }

            }
        }
        return this.parStack.empty();
    }

    public boolean isOpenPar(char ch){
        return(ch == '(' || ch == '[' || ch == '{');
    }

    public boolean isClosePar(char ch){
        return(ch == ')' || ch == ']' || ch == '}');
    }

    public boolean isCloseMatch(char open, char close){
        return(open == '(' && close == ')' || open == '[' && close == ']' || open == '{' && close == '}');
    }

}

