package il.co.ilrd.singleton;

//Lazy Double-checked locking thread-safe
public class SingletonLazyDoublCheckedSafe {
    private static volatile SingletonLazyDoublCheckedSafe obj  = null;
  
    private SingletonLazyDoublCheckedSafe() {}
 
    public static SingletonLazyDoublCheckedSafe getInstance()
    {
        if (obj == null)
        {
            synchronized (SingletonLazyDoublCheckedSafe.class)
            {
                if (obj==null)
                    obj = new SingletonLazyDoublCheckedSafe();
            }
        }
        return obj;
    }
    
}
