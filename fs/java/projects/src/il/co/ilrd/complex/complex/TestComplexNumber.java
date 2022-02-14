package complex;

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

        if (n1.isImag(n1)){
            System.out.println("failed in isimag");
        }

        if (n2.isReal(n2)){
            System.out.println("failed in isreal");
        }

        if (0 < n1.compareTo(n2)){
            System.out.println("failed in compareTo");
        }

        ComplexNumber parsingResult = ComplexNumber.parsing("3+8i");
        System.out.println(parsingResult.toString());


        System.out.println("test done!");
    }  

}
