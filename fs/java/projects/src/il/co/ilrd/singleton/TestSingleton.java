package il.co.ilrd.singleton;


public class TestSingleton {

    public static void TestLazyNotSafe() {	
        SingletonLazyNotSafe t1 = SingletonLazyNotSafe.getInstance();
        SingletonLazyNotSafe t2 = SingletonLazyNotSafe.getInstance();
        if (t1 != t2){
            System.out.println("TestLazyNotSafe failed\n\n");
        }

	}
	
	public static void TestLazyDoublCheckedSafe() {
        
        SingletonLazyDoublCheckedSafe t1 = SingletonLazyDoublCheckedSafe.getInstance();
        SingletonLazyDoublCheckedSafe t2 = SingletonLazyDoublCheckedSafe.getInstance();
        if (t1 != t2){
            System.out.println("LazyDoublCheckedSafe failed\n\n");
        }

	}
	
	public static void TestEagerInitialization() {
        
        SingletonEagerInitialization t1 = SingletonEagerInitialization.getInstance();
        SingletonEagerInitialization t2 = SingletonEagerInitialization.getInstance();
        if (t1 != t2){
            System.out.println("EagerInitialization failed\n\n");
        }
	
	}
	
	public static void TestHolderNestedClass() {
        
        SingletonHolderNestedClass t1 = SingletonHolderNestedClass.getInstance();
        SingletonHolderNestedClass t2 = SingletonHolderNestedClass.getInstance();
        if (t1 != t2){
            System.out.println("HolderNestedClass failed\n\n");
        }

	}
	
	public static void TestEnumSingleton() {
        
        SingletonEnumSingleton t1 = SingletonEnumSingleton.getInstance();
        SingletonEnumSingleton t2 = SingletonEnumSingleton.getInstance();
        if (t1 != t2){
            System.out.println("EnumSingleton failed\n\n");
        }
	}
	
	public static void main(String[] args) {
		//TestLazyNotSafe();
		//TestLazyDoublCheckedSafe();
		//TestEagerInitialization();
		//TestHolderNestedClass();
		TestEnumSingleton();
	}

}

