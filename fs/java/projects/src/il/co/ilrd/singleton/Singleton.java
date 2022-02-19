package il.co.ilrd.singleton;

//Lazy Not thread-safe
public class Singleton {
    
    private static Singleton obj;
    private Singleton() {}
 
    public static Singleton getInstance()
    {
        if (obj==null)
            obj = new Singleton();
        return obj;
    }
}

 //Lazy Double-checked locking thread-safe
 public class Singleton
 {
     private static volatile Singleton obj  = null;
  
     private Singleton() {}
  
     public static Singleton getInstance()
     {
         if (obj == null)
         {
             synchronized (Singleton.class)
             {
                 if (obj==null)
                     obj = new Singleton();
             }
         }
         return obj;
     }
 }

 //Thread-safe but not lazy initialized (Eager initialization)
 public class Singleton
{
    private static Singleton obj = new Singleton();
 
    private Singleton() {}
 
    public static Singleton getInstance()
    {
        return obj;
    }
}

//Thread-safe and lazy initialized (using SingletonHolder nested class)
public class Singleton{
  private Singleton(){}

  private static class BillPughSingleton{
    private static final Singleton INSTANCE = new Singleton();
  }
 
  public static Singleton getInstance(){
    return BillPughSingleton.INSTANCE;
  }
}

//enum Singleton 
public enum Singleton {
    INSTANCE;
  
}
class Main {
    public static void main(String[] args) {
        Singleton singleton = Singleton.INSTANCE;
  
    }
} 