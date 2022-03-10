package il.co.ilrd.factory;

import java.util.function.Function;

public class FactoryTest {
    public static void main(String[] args) {
        Factory<Animal, String, String> animalFactory = new Factory<>();

        Function<String,Dog> dogCtor = (str) -> new Dog();
        Function<String,Cat> catCtor = (name) -> new Cat(name);
        Function<String,Cat> catCtor2 = (name) -> new Cat();
        Function<String,Elephant> elephCtor = new Function<>() {

            @Override
            public Elephant apply(String t) {
                return new Elephant() ;
            }
            
        };

        Function<String,Cat> catCtor3 = new Function<>() {

            @Override
            public Cat apply(String t) {
                return new Cat(t) ;
            }
            
        };
        
        Function<String,Dog> dogCtor2 = (str) -> SugarRef.dogCtorSugar();
        //Function<String,Dog> dogCtor3 = SugarRef::dogCtorSugar(str);

        animalFactory.add("Dog", dogCtor);
        animalFactory.add("Cat", catCtor);
        animalFactory.add("Cat2", catCtor2);
        animalFactory.add("elephant", elephCtor);
        animalFactory.add("Cat3", catCtor3);
        animalFactory.add("Dog2", dogCtor2);
        //animalFactory.add("Dog3", dogCtor3);

        Animal mydog = animalFactory.create("Dog");
        Animal mycat = animalFactory.create("Cat", "jerry");
        Animal mycat2 = animalFactory.create("Cat2");
        Animal myelephant = animalFactory.create("elephant");
        Animal mycat3 = animalFactory.create("Cat3", "josef");
        Animal mydog2 = animalFactory.create("Dog2");
        //Animal mydog3 = animalFactory.create("Dog3");
    } 
    
}

interface Animal{
    public void print();
}

class Dog implements Animal{
    public Dog(){
        print();
    }

    @Override
    public void print(){
        System.out.println("im dog");
    }
}

class Cat implements Animal{
    String name;

    public Cat(){
        print();
    }

    public Cat(String name){
        this.name = name;
        print();
        System.out.println("my name is: " + name);
    }

    @Override
    public void print(){
        System.out.println("im cat");
    }
}

class Elephant implements Animal{
    public Elephant(){
        print();
    }

    @Override
    public void print(){
        System.out.println("im elephant");
    }
}

class SugarRef{
    public static Cat catCtorSugar(String str){
        return new Cat(str);
    }  
    
    public static Dog dogCtorSugar(){
        return new Dog();
    }
}



    