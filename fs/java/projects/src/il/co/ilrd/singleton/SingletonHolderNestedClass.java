package il.co.ilrd.singleton;

//Thread-safe and lazy initialized (using SingletonHolder nested class)
public class SingletonHolderNestedClass {
    private SingletonHolderNestedClass(){}

    private static class NestedClass{
      private static final SingletonHolderNestedClass instance = new SingletonHolderNestedClass();
    }
   
    public static SingletonHolderNestedClass getInstance(){
      return NestedClass.instance;
    }
    
}
