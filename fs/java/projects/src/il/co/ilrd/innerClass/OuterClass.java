package il.co.ilrd.innerClass;

interface Age {
    int x = 21;
    void getAge();
}

public class OuterClass {
    int myouter;
    public OuterClass(int myouter){
        this.myouter = myouter;
    }
    
    public void PrintMe(){
        System.out.println(myouter);
    } 

    public class innerClass{
        
        public void test(){
            OuterClass.this.PrintMe();
            OuterClass.this.myouter = 9;
            OuterClass.this.PrintMe();
        }

        public void testAnonymous(){
            Age oj1 = new Age() {
           
                @Override public void getAge()
                {
                    System.out.print("Age is " + x);
                }
            };
           
            oj1.getAge();
        }
    }

    public static void main(String[] args) {
        innerClass obj = new OuterClass(6).new innerClass();
        obj.test();
        obj.testAnonymous();

    }
        
        
     
}
