/*Reviewer: Shiraz*/

package vending_machine;

import java.util.List;
import java.util.ListIterator;

public class VendingMachine {
    private VMstate currState;
    private List <Product> list;
    private int moneyIn;
    private ScreenOutput output;
    
    //constructor
    public VendingMachine(List <Product> list,ScreenOutput output){
        this.list = list;
        this.output = output;
        moneyIn = 0;
        currState = VMstate.WFP;
    }

    public void payment(int amount){
        currState.payment(this, amount);
    }
    public void chooseProduct(String product){
        currState.chooseProduct(this, product);
    }
    public void cancel(){
        currState.cancel(this);
    }

    private enum VMstate {
        WFP {
            @Override
            public void chooseProduct(VendingMachine vm, String product){
                vm.output.PrintToMachine("please insert money before selection");
            }
            
        }, WFS {
            @Override
            public void chooseProduct(VendingMachine vm, String product){
                ListIterator<Product> listIter = vm.list.listIterator();
                while(listIter.hasNext()){
                    Product temp = listIter.next();
                    if (temp.getName().equalsIgnoreCase(product)){
                        if(vm.moneyIn >= temp.getPrice()){
                            vm.moneyIn -= temp.getPrice();
                            vm.output.PrintToMachine("enjoy your product, take the change:" + vm.moneyIn);
                            vm.moneyIn = 0;
                            vm.currState = VMstate.WFP;
                        }
                        else{
                            vm.output.PrintToMachine("not enough money for this product, please add " + (temp.getPrice()- vm.moneyIn) + " or cancel");
                        }
                        return;
                    }  
                }
                vm.output.PrintToMachine("please choose another product or cancel");
            }
        };

        public void payment(VendingMachine vm, int amount){
            vm.moneyIn +=amount;
            vm.currState = VMstate.WFS;
            vm.output.PrintToMachine("Thank you, amount of money in the machine:" + vm.moneyIn);
        }
        public abstract void chooseProduct(VendingMachine vm, String product);
        
        public void cancel(VendingMachine vm){
            vm.output.PrintToMachine("The deal was cancled, please take your money " + vm.moneyIn);
            vm.currState = VMstate.WFP;
            vm.moneyIn = 0;
        }

    }

}




