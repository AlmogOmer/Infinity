package il.co.ilrd.singleton;


public class TestSingleton {

    public static void TestLazyNotSafe() {	
        LazyNotSafe t1 = LazyNotSafe.getInstance();
        LazyNotSafe t2 = LazyNotSafe.getInstance();
        if (t1 != t2){
            System.out.println("TestLazyNotSafe failed\n\n");
        }

	}
	
	public static void TestLazyDoublCheckedSafe() {
        
        LazyDoublCheckedSafe t1 = LazyDoublCheckedSafe.getInstance();
        LazyDoublCheckedSafe t2 = LazyDoublCheckedSafe.getInstance();
        if (t1 != t2){
            System.out.println("LazyDoublCheckedSafe failed\n\n");
        }

	}
	
	public static void TestEagerInitialization() {
        
        EagerInitialization t1 = EagerInitialization.getInstance();
        EagerInitialization t2 = EagerInitialization.getInstance();
        if (t1 != t2){
            System.out.println("EagerInitialization failed\n\n");
        }
	
	}
	
	public static void TestHolderNestedClass() {
        
        HolderNestedClass t1 = HolderNestedClass.getInstance();
        HolderNestedClass t2 = HolderNestedClass.getInstance();
        if (t1 != t2){
            System.out.println("HolderNestedClass failed\n\n");
        }

	}
	
	public static void TestEnumSingleton() {
        
        EnumSingleton t1 = EnumSingleton.getInstance();
        EnumSingleton t2 = EnumSingleton.getInstance();
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

