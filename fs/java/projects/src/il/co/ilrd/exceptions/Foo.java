package il.co.ilrd.exceptions;

import java.io.IOException;

public class Foo {
    
    public static void func1() throws IOException{
        throw new IOException();
        
    }

    public static void func2(){
        throw new NullPointerException();
        
    }
    
    public static void func3() throws MyException1{
        throw new MyException1();
        
    }

    public static void func4() throws MyException2{
        throw new MyException2();
        
    }


    public static void main(String[] args) {
        byte[] mybyte = new byte[100];
        System.out.println(mybyte[101]);
        
        try {
            func1();
        } catch (IOException e) {
            e.printStackTrace();
        }
        
        func2();

        try {
            func3();
        } catch (MyException1 e) {
            e.printStackTrace();
        }

        try {
            func4();
        } catch (MyException2 e) {
            e.printStackTrace();
        }
    }
}

class MyException1 extends RuntimeException {
}

class MyException2 extends IOException {
}

