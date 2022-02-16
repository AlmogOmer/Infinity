/*Reviewer: Shiraz*/

package vending_machine;

import java.util.List;
import java.util.ListIterator;

public class VendingMachine {
    private VMstate currState;
    private List <Product> list;
    private int moneyIn;
    private ScreenOutput output;
    private boolean isRunning;
    private VMThread thread;
    private long startTime;
    
    //constructor
    public VendingMachine(List <Product> list,ScreenOutput output){
        this.list = list;
        this.output = output;
        moneyIn = 0;
        currState = VMstate.OFF;
        isRunning = false;
        thread = new VMThread();
    }

    private class VMThread extends Thread {
        @Override
        public void run() {
            while (isRunning) {
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                currState.checkTimeOut(VendingMachine.this);
            }
        }
    }

    public void turnOnMachine(){
        currState.turnOnMachine(this);
    }

    public void turnOffmachine() throws InterruptedException {
        currState.turnOffMachine(this);
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
        OFF{
            @Override
            public void payment(VendingMachine vm, int amount){
                vm.output.PrintToMachine("machine is off");
            }
            @Override
            public void cancel(VendingMachine vm){
                vm.output.PrintToMachine("machine is off");
            }
            @Override
            public void chooseProduct(VendingMachine vm, String product){
                vm.output.PrintToMachine("machine is off");
            }
            @Override
            public void turnOnMachine(VendingMachine vm){
                vm.isRunning = true;
                vm.currState = VMstate.WFP;
                vm.thread.start();
            }

            @Override 
            public void turnOffMachine(VendingMachine vm){}

        },
        WFP {
            @Override
            public void chooseProduct(VendingMachine vm, String product){
                vm.output.PrintToMachine("please insert money before selection");
            }

            
        }, WFS {
            @Override
            public void checkTimeOut(VendingMachine vm){
                if(System.currentTimeMillis() - vm.startTime > 10000){
                    cancel(vm);
                }
            }
            
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
            vm.startTime = System.currentTimeMillis();
            vm.output.PrintToMachine("Thank you, amount of money in the machine:" + vm.moneyIn);
        }
        public abstract void chooseProduct(VendingMachine vm, String product);
        
        public void cancel(VendingMachine vm){
            vm.output.PrintToMachine("The deal was cancled, please take your money " + vm.moneyIn);
            vm.currState = VMstate.WFP;
            vm.moneyIn = 0;
        }

        public void checkTimeOut(VendingMachine vm){}

        public void turnOnMachine(VendingMachine vm){}
        
        public void turnOffMachine(VendingMachine vm) throws InterruptedException{
            vm.isRunning = false;
            vm.currState = VMstate.OFF;
            vm.thread.join();
        }

    }

}




