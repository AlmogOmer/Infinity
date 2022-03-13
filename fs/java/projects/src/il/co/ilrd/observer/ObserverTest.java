package il.co.ilrd.observer;

import java.util.function.Consumer;

public class ObserverTest {
    
}

class Subject{

}

class Observer{
    Consumer<String> myupdate = new Consumer<String>() {
        @Override
        
    };

    Runnable mystopService = new Runnable() {
        @Override
    };
    
    Callback <String> mycall = new Callback<>(myupdate, mystopService)
}
