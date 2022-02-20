package il.co.ilrd.singleton;

 //Thread-safe but not lazy initialized (Eager initialization)
public class EagerInitialization {
    private static final EagerInitialization obj = new EagerInitialization();
 
    private EagerInitialization() {}
 
    public static EagerInitialization getInstance()
    {
        return obj;
    }
    
}
