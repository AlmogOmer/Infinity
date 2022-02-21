package il.co.ilrd.singleton;

//enum Singleton 
public enum SingletonEnumSingleton {
    INSTANCE;

    public static SingletonEnumSingleton getInstance(){
        return SingletonEnumSingleton.INSTANCE;
    }
  
}