
/*Set<E>
Map<K,V>
AtomicReference<T>*/

   // Typesafe heterogeneous container pattern - API
   public class Favorites {
    public <T> void putFavorite(Class<T> type, T instance){};
    public <T> T getFavorite(Class<T> type){};
}


   // Typesafe heterogeneous container pattern - client
   public static void main(String[] args) {
    Favorites f = new Favorites();
    f.putFavorite(String.class, "Java");
    f.putFavorite(Integer.class, 0xcafebabe);
    f.putFavorite(Class.class, Favorites.class);
    String favoriteString = f.getFavorite(String.class);
    int favoriteInteger = f.getFavorite(Integer.class);
    Class<?> favoriteClass = f.getFavorite(Class.class);
    System.out.printf("%s %x %s%n", favoriteString,favoriteInteger, favoriteClass.getName());
}

//As you would expect, this program prints Java cafebabe Favorites.

// Typesafe heterogeneous container pattern - implementation
public class Favorites {
    private Map<Class<?>, Object> favorites = new HashMap<>();
    public <T> void putFavorite(Class<T> type, T instance) {
        favorites.put(Objects.requireNonNull(type), instance);
    }
    public <T> T getFavorite(Class<T> type) { 
        return type.cast(favorites.get(type));
    }
} 

/*Map<Class<?>, : This means that every key can have a different parameterized type: 
one can be Class<String>, the next Class<Integer>, and so on. */

/*So what does the cast method do for us, given that it simply returns its argument? 
The signature of the cast method takes full advantage of the fact that class Class is generic.
Its return type is the type parameter of the Class object:*/
   public class Class<T> {
       T cast(Object obj){};
}

  // Achieving runtime type safety with a dynamic cast
  public <T> void putFavorite(Class<T> type, T instance) {
    favorites.put(type, type.cast(instance));
}


/*The class literal List<String>.class is a syntax error. 
List<String> and List<Integer> share a single Class object, which is List.class.*/


public <T extends Annotation>{
    T getAnnotation(Class<T> annotationType){};
}

/*Suppose you have an object of type*/ Class<?> 
/*and you want to pass it to a method such as getAnnotation. 
You could cast the object to:*/

Class<? extends Annotation> /*this cast is unchecked*/

/*class Class provides an instance method that performs this cast safely and dynamically.
The method is called asSubclass:*/ 

public <U> Class<? extends U> asSubclass(Class<U> clazz){};

/*U - Type to cast this class object to

clazz - class of the type to cast this class object to.*/

/*This method is useful when a client needs to "narrow" the type
of a Class object to pass it to an API 
that restricts the Class objects that it is willing to accept.*/

/*it casts the Class object on which it is called
to represent a subclass of the class represented by its argument.

If the cast succeeds, the method returns its argument; 
if it fails, it throws a ClassCastException.
Here’s how you use the asSubclass method to read an annotation 
whose type is unknown at compile time.*/


   // Use of asSubclass to safely cast to a bounded type token
   static Annotation getAnnotation(AnnotatedElement element,String annotationTypeName) {
        Class<?> annotationType = null; // Unbounded type token 
        try {
            annotationType = Class.forName(annotationTypeName);
       }catch (Exception ex) {
           throw new IllegalArgumentException(ex);
       }
        return element.getAnnotation( annotationType.asSubclass(Annotation.class));
}

/*In summary, the normal use of generics, exemplified by the collections APIs, 
restricts you to a fixed number of type parameters per container. 
You can get around this restriction by placing the type parameter on the key 
rather than the container. You can use Class objects as keys for such 
typesafe heterogeneous containers. 
A Class object used in this fashion is called a type token.*/
