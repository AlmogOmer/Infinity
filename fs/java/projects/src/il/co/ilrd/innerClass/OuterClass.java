package il.co.ilrd.innerClass;

public class OuterClass {
    int myouter;
    public OuterClass(int myouter){
        this.myouter = myouter;
    }
    
    public void PrintMe(int myouter){
        System.out.println(myouter);
    } 

    public class innerClass{
        
        //OuterClass.PrintMe(myouter);
   
    }

    public static void main(String[] args) {
    }
        
        
     
}
