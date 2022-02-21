package il.co.ilrd.singleton;

//Lazy Not thread-safe
public class SingletonLazyNotSafe {
    
    private static SingletonLazyNotSafe obj;
    private SingletonLazyNotSafe() {}
 
    public static SingletonLazyNotSafe getInstance()
    {
        if (obj==null)
            obj = new SingletonLazyNotSafe();
        return obj;
    }
}



