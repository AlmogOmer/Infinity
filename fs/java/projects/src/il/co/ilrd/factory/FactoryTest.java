/*Reviwer : Ofek*/

package il.co.ilrd.factory;

import java.lang.reflect.InvocationTargetException;
import java.util.function.Function;

public class FactoryTest {
    public static void main(String[] args) {
        Factory<Animal, String, String> animalFactory = new Factory<>();
        /*Test 1*/
        Function<String,Dog> dogCtor = (str) -> new Dog();
        Function<String,Cat> catCtor = (name) -> new Cat(name);
        Function<String,Cat> catCtor2 = (name) -> new Cat();

        /*Test 2*/
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
        
        /*Test 3*/
        Function<String,Dog> dogCtor2 = (str) -> SugarRef.dogCtorSugar();
        Function<String,Cat> catCtor4 = SugarRef :: catCtorSugar;

        /*Test 4*/
        Function<String,Bird> birdCtor = new Bird() :: birdInstance;

        /*Test 5*/
        //Function<String,Elephant> elephantCtor = Class.forName("il.co.ilrd.factory.Elephant") :: getConstructor().newInstance();
           
     

        animalFactory.add("Dog", dogCtor);
        animalFactory.add("Cat", catCtor);
        animalFactory.add("Cat2", catCtor2);
        animalFactory.add("elephant", elephCtor);
        animalFactory.add("Cat3", catCtor3);
        animalFactory.add("Dog2", dogCtor2);
        animalFactory.add("Cat4", catCtor4);
        animalFactory.add("Bird", birdCtor);
        //animalFactory.add("elephant2", elephantCtor);

        Animal mydog = animalFactory.create("Dog");
        Animal mycat = animalFactory.create("Cat", "jerry");
        Animal mycat2 = animalFactory.create("Cat2");
        Animal myelephant = animalFactory.create("elephant");
        Animal mycat3 = animalFactory.create("Cat3", "josef");
        Animal mydog2 = animalFactory.create("Dog2");
        Animal mycat4 = animalFactory.create("Cat4");
        Animal mybird = animalFactory.create("Bird");
        Animal mybird2 = animalFactory.create("Bird", "eagle");
        //Animal myelephant2 = animalFactory.create("elephant2");
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
    private String name;

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

class Bird implements Animal{
    private String name;

	public Bird() {
		this("singBird");
	}
	
	public Bird(String name) {
		this.name = name;
        print();
        System.out.println("my name is: " + name);
	}
	
    @Override
    public void print(){
        System.out.println("im Bird");
    }
  
  public Bird birdInstance(String str){
  	if (str == null) {
  		return new Bird();
  	}
  	else {
  		return new Bird(str);
  	}
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



    