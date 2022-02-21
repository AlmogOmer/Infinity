package il.co.ilrd.reflection;
import java.lang.reflect.*;

public class TestFoo {
    public static void main(String args[]) throws NoSuchMethodException, SecurityException, IllegalAccessException, IllegalArgumentException, InvocationTargetException, NoSuchFieldException 
    {
        Foo obj = new Foo();
        Class cls = obj.getClass();
        System.out.println("The name of class is " + cls.getName());
        System.out.println("The name of subclass is " + cls.getSuperclass());
        
        Constructor constructor = cls.getConstructor();
        System.out.println("The name of constructor is " + constructor.getName());
  
        System.out.println("The public methods of class are : ");
  
        Method[] methods = cls.getMethods();
  
        for (Method method:methods)
            System.out.println(method.getName());
  
        //Method methodcall1 = cls.getDeclaredMethod("method2");
   
        //methodcall1.invoke(obj, 19);
  
        Field field = cls.getDeclaredField("s");
  
        field.setAccessible(true);

        field.set(obj, "JAVA");

        Method methodcall2 = cls.getDeclaredMethod("method1");
  
        methodcall2.invoke(obj);
  
        Method methodcall3 = cls.getDeclaredMethod("method3");

        methodcall3.setAccessible(true);

        methodcall3.invoke(obj);
    }
    
}
