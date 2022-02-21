package il.co.ilrd.singleton;

 //Thread-safe but not lazy initialized (Eager initialization)
public class SingletonEagerInitialization {
    private static final SingletonEagerInitialization obj = new SingletonEagerInitialization();
 
    private SingletonEagerInitialization() {}
 
    public static SingletonEagerInitialization getInstance()
    {
        return obj;
    }
    
}
