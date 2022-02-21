package il.co.ilrd.reflection;


public class Foo {
    private String s;

    public Foo(){}

    public void method1()  {
        System.out.println("The string is " + s);
    }

    public void method2(int n)  {
        System.out.println("The number is " + n);
    }
  
    private void method3() {
        System.out.println("Private method invoked");
    }

    

}
