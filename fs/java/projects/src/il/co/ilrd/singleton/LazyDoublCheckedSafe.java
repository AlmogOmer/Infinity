package il.co.ilrd.singleton;

//Lazy Double-checked locking thread-safe
public class LazyDoublCheckedSafe {
    private static volatile LazyDoublCheckedSafe obj  = null;
  
    private LazyDoublCheckedSafe() {}
 
    public static LazyDoublCheckedSafe getInstance()
    {
        if (obj == null)
        {
            synchronized (LazyDoublCheckedSafe.class)
            {
                if (obj==null)
                    obj = new LazyDoublCheckedSafe();
            }
        }
        return obj;
    }
    
}
