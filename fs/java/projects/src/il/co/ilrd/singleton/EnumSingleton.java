package il.co.ilrd.singleton;

//enum Singleton 
public enum EnumSingleton {
    INSTANCE;

    public static EnumSingleton getInstance(){
        return EnumSingleton.INSTANCE;
    }
  
}