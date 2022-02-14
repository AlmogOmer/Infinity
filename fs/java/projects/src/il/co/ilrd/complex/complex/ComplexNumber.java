package complex;

public class ComplexNumber implements Comparable<ComplexNumber> {
    private double real;
    private double imag;
    
    private ComplexNumber(double real, double imag){
       this.real = real;
       this.imag = imag;
    }

    public static ComplexNumber createFromReal(double real)
    {
        return new ComplexNumber(real,0);
    }

    public static ComplexNumber createFromImag(double imag)
    {
        return new ComplexNumber(0,imag);
    }

    public double getReal()
    {
        return real;
    }

    public void setReal(double real)
    {
        this.real = real;
    }

    public double getImg()
    {
        return imag;
    }

    public void setImg(double imag)
    {
        this.imag = imag;
    }


    public static ComplexNumber add(ComplexNumber n1, ComplexNumber n2){
        ComplexNumber temp = new ComplexNumber(0,0);
        temp.real = n1.real + n2.real;
        temp.imag = n1.imag + n2.imag;
        return(temp);
    }

    public static ComplexNumber sub(ComplexNumber n1, ComplexNumber n2){
        ComplexNumber temp = new ComplexNumber(0,0);
        temp.real = n1.real - n2.real;
        temp.imag = n1.imag - n2.imag;
        return(temp);
    }

    public static ComplexNumber mul(ComplexNumber n1, ComplexNumber n2){
        ComplexNumber temp = new ComplexNumber(0,0);
        temp.real = n1.real*n2.real - n1.imag*n2.imag;
        temp.imag = n1.real*n2.imag + n1.imag*n2.real;
        return(temp);
    }

    public static ComplexNumber div(ComplexNumber n1, ComplexNumber n2){
        ComplexNumber temp = new ComplexNumber(0,0);
        temp.real = (n1.real*n2.real + n1.imag*n2.imag)/(n2.real*n2.real + n2.imag*n2.imag);
        temp.imag = (n1.imag*n2.real - n1.real*n2.imag)/(n2.real*n2.real + n2.imag*n2.imag);
        return(temp);
    }

    
    public boolean isReal(ComplexNumber n){
        return this.imag == 0;
    }

    public boolean isImag(ComplexNumber n){
        return this.real == 0;
    }

    @Override
    public int compareTo(ComplexNumber n){

        if ( 0 > this.real- n.real){
            return -1;
        } 

        else if ( 0 < this.real- n.real){
            return 1;
        }

        return 0;
    }

    @Override
    public String toString(){
        return "The complex number is " + this.real + " + " + this.imag + "i";
    }

    @Override
    public boolean equals(Object n){
        if (n instanceof ComplexNumber) {
            ComplexNumber other = (ComplexNumber)n;
            return (
                this.real == other.real &&
                this.imag == other.imag
            );
        }
        return false;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        long temp;
        temp = Double.doubleToLongBits(imag);
        result = prime * result + (int) (temp ^ (temp >>> 32));
        temp = Double.doubleToLongBits(real);
        result = prime * result + (int) (temp ^ (temp >>> 32));
        
        return result;

    }

    public static ComplexNumber parsing(String str){
        
        ComplexNumber result = new ComplexNumber(0,0);
        int i = 0;
        while(str.charAt(i) > '0' && str.charAt(i) < '9' && i < str.length())
        {
            result.real = result.real*10 + (double)(str.charAt(i)- '0');
            ++i;
        }

        ++i;

        while(str.charAt(i) > '0' && str.charAt(i) < '9' && i < str.length())
        {
            result.imag = result.imag*10 + (double)(str.charAt(i)-'0');
            ++i;
        }


        return result;

    }


    
 }