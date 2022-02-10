public class LinkedList_test {
    public static void main(String[] args) {

        LinkedList list = new LinkedList();
        if(!list.IsEmpty())
        {
            System.out.println("isempty failed");
        }
        
        Integer x1 = 1;
        Integer x2 = 2;
        Integer x3 = 3;
        Integer x4 = 4;
        Iter iter = list.Begin();

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

        if (list.Find(x3).Next() != x3)
        {
            System.out.println("find x3 failed");
        }

        if (list.Find(x1).Next() != x1)
        {
            System.out.println("find x1 failed");
        }

        System.out.println("test done!");
    }
}


