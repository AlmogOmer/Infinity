package il.co.ilrd.complex;

public class TestComplexNumber{
    public static void main(String[] args){
        ComplexNumber n1 = ComplexNumber.createFromReal(3);
        n1.setImg(4);
        System.out.println(n1.toString());
        System.out.println("n1 hash code is : " + n1.hashCode());

        ComplexNumber n2 = ComplexNumber.createFromReal(7);
        n2.setImg(2);
        System.out.println(n2.toString());
        System.out.println("n2 hash code is : " + n2.hashCode());

        ComplexNumber addResult = ComplexNumber.add(n1, n2);
        System.out.println(addResult.toString());

        ComplexNumber subResult = ComplexNumber.sub(n1, n2);
        System.out.println(subResult.toString());

        ComplexNumber mulResult = ComplexNumber.mul(n1, n2);
        System.out.println(mulResult.toString());

        ComplexNumber divResult = ComplexNumber.div(n1, n2);
        System.out.println(divResult.toString());

        if (n2.equals(n1)){
            System.out.println("failed in equals");
        }

        if (n1.isImag()){
            System.out.println("failed in isimag");
        }

        if (n2.isReal()){
            System.out.println("failed in isreal");
        }

        if (0 < n1.compareTo(n2)){
            System.out.println("failed in compareTo");
        }

        ComplexNumber parsingResult1 = ComplexNumber.parsing("3 +8i");
        System.out.println(parsingResult1.toString());

        /*ComplexNumber parsingResult2 = ComplexNumber.parsing("3i");
        System.out.println(parsingResult2.toString());

        ComplexNumber parsingResult3 = ComplexNumber.parsing("-3i+9");
        System.out.println(parsingResult3.toString());

        ComplexNumber parsingResult4 = ComplexNumber.parsing("-3i-9");
        System.out.println(parsingResult4.toString());*/

        ComplexNumber parsingResult3 = ComplexNumber.parsing("-31 -9i");
        System.out.println(parsingResult3.toString());
        
        /*ComplexNumber parsingResult5 = ComplexNumber.parsing("92");
        System.out.println(parsingResult5.toString());*/


        System.out.println("test done!");
    }  

}
