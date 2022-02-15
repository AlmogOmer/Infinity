package fsm;

public class VM {
    States state;
    //constructor
    public VM(List <Product>){}

    public void payment(int amount){}
    public boolean chooseProduct(Product product){}
    public void cancle(){}

}

interface VMS {
    public void payment(int amount){}
    public boolean chooseProduct(Product product){}
    public void cancle(){}
}

enum States implements VMS {
    WFP {
        @Override
        public void payment(int amount){}
        @Override
        public boolean chooseProduct(Product product){}
        @Override
        public void cancle(){}
        
    }, WFS {
        @Override
        public void payment(int amount){}
        @Override
        public boolean chooseProduct(Product product){}
        @Override
        public void cancle(){}
        
    }
}


public class Product{
    private int price;
    private String name;

    //constructor
    public Product(int price, String name){}

    public int getPrice(){}
    public String getName(){}

}