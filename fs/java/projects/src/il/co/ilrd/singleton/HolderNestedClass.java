package il.co.ilrd.singleton;

//Thread-safe and lazy initialized (using SingletonHolder nested class)
public class HolderNestedClass {
    private HolderNestedClass(){}

    private static class NestedClass{
      private static final HolderNestedClass instance = new HolderNestedClass();
    }
   
    public static HolderNestedClass getInstance(){
      return NestedClass.instance;
    }
    
}
