package il.co.ilrd.singleton;

//Lazy Not thread-safe
public class LazyNotSafe {
    
    private static LazyNotSafe obj;
    private LazyNotSafe() {}
 
    public static LazyNotSafe getInstance()
    {
        if (obj==null)
            obj = new LazyNotSafe();
        return obj;
    }
}



