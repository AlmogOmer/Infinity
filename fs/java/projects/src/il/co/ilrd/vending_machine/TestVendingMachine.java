package il.co.ilrd.vending_machine;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.TimeUnit;

public class TestVendingMachine {

    public class PrintScreen implements ScreenOutput{
        public void PrintToMachine(String output){
            System.out.println(output);
        }
    }

    public class ProductImp implements Product{
        public int price;
        public String name;

        //constructor
        public ProductImp(int price, String name){
            this.price = price;
            this.name = name;
        }

        public int getPrice(){
            return price;
        }
        public String getName(){
            return name;

        }
    }

    public static void main(String[] args) throws InterruptedException {
        
        TestVendingMachine.PrintScreen output = new TestVendingMachine().new PrintScreen();
        List <Product> list_prod = new ArrayList<Product>();
        
        list_prod.add(new TestVendingMachine().new ProductImp(8, "coke"));
        list_prod.add(new TestVendingMachine().new ProductImp(9, "sprite"));
        list_prod.add(new TestVendingMachine().new ProductImp(11, "fanta"));
        list_prod.add(new TestVendingMachine().new ProductImp(7, "water"));
    
        VendingMachine vm = new VendingMachine(list_prod,output);

        vm.payment(17);
        vm.chooseProduct("sprite");
        vm.payment(3);
        vm.chooseProduct("coke");
        vm.payment(5);
        vm.chooseProduct("coke");
        vm.chooseProduct("coke");
        vm.turnOnMachine();
        vm.payment(17);
        
        TimeUnit.SECONDS.sleep(15);
       
        vm.chooseProduct("sprite");
        vm.payment(5);
        vm.chooseProduct("orange");
        vm.chooseProduct("sprite");
        vm.cancel();
        vm.payment(5);
        
        vm.turnOffmachine();
        vm.chooseProduct("coke");
        
        vm.turnOnMachine();
        vm.payment(17);
        vm.chooseProduct("coke");
        vm.turnOffmachine();
    }

    
}


