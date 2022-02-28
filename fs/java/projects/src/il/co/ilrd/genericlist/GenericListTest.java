package il.co.ilrd.genericlist;

import java.util.Iterator;

public class GenericListTest {
    public static void main(String[] args) {

        GenericList<Integer> list = new GenericList<Integer>();
        GenericList<Integer> list1 = new GenericList<Integer>();
        if(!list.IsEmpty())
        {
            System.out.println("isempty failed");
        }
        
        Integer x1 = 1;
        Integer x2 = 2;
        Integer x3 = 3;
        Integer x4 = 4;

        Integer y1 = 10;
        Integer y2 = 20;
        Integer y3 = 30;
        Integer y4 = 40;

        list.PushFront(x1);
        if(list.IsEmpty())
        {
            System.out.println("isempty failed");
        }
        if(list.Size() != 1)
        {
            System.out.println("size failed");
        }
        if(list.Find(1) == null)
        {
            System.out.println("find failed");
        }

        list.PopFront();
        if(!list.IsEmpty())
        {
            System.out.println("isempty failed");
        }
        if(list.Size() != 0)
        {
            System.out.println("size failed");
        }
        if(list.Find(1) != null)
        {
            System.out.println("find failed");
        }

        list.PushFront(x1);
        list.PushFront(x2);
        list.PushFront(x3);
        list.PushFront(x4);

        if(list.Size() != 4)
        {
            System.out.println("size failed");
        }

        if (list.Find(x3).next() != x3)
        {
            System.out.println("find x3 failed");
        }

        if (list.Find(x1).next() != x1)
        {
            System.out.println("find x1 failed");
        }

        list1.PushFront(y1);
        Iterator<Integer> iter = list1.iterator();
        while (iter.hasNext()) {
            System.out.println(iter.next());    //should throw exception //
            list1.PushFront(y2);
        }
        
        list1.PushFront(y3);
        list1.PushFront(y4);

        System.out.println("\n****list****\n");
        for( Integer element : list ){
            System.out.println( element );
        }
        System.out.println("\n****list1****\n");
        for( Integer element : list1 ){
            System.out.println( element );
        }
        System.out.println("\n****list1 after revers****\n");
        for( Integer element : GenericList.reversList(list1) ){
            System.out.println( element );
        }
        System.out.println("\n****list1 & list after merge****\n");
        for( Integer element : GenericList.merge(list1, list) ){
            System.out.println( element );
        }


        System.out.println("\ntest done!\n");
    }
}
