package il.co.ilrd.generics;

public class TestGenerics {
    public static <T> void printArray(T array[]){
        for(T element : array){
            System.out.println(element);
        }
    }

    public static void main(String[] args) {
        Integer array1[] = {3,2,5,1};
        String array2[] = {"hello","i","am","here"};
        Double array3[] = {3.1,7.8,8.8};

        Integer a = 3;
        String b = "hello";
        Double c = 3.1;

        TestGenerics.printArray(array1);
        TestGenerics.printArray(array2);
        TestGenerics.printArray(array3);

        FooReference<Integer> r1 = new FooReference<>(a);
        FooReference<String> r2 = new FooReference<>(b);
        FooReference<Double> r3 = new FooReference<>(c);

        System.out.println(r1.getter());
        System.out.println(r2.getter());
        System.out.println(r3.getter());
        r1.setter(7);
        System.out.println(r1.getter());

    }
}

class FooReference<T> {
    T data;

    public FooReference(T data){
        this.data = data;
    }

    public void setter(T data){
        this.data = data;
    }

    public T getter(){
        return data;
    }
}