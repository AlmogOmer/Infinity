public class Complex implements Comparable<Complex> {
    private double real;
    private double imag;
    
    private Complex(double real, double imag){
       this.real = real;
       this.imag = imag;
    }

    public double getReal(Complex n)
    {
        return this.real;
    }

    public void setReal(double real)
    {
        this.real = real;
    }

    public double getImag(Complex n)
    {
        return this.imag;
    }

    public void setImag(double imag)
    {
        this.imag = imag;
    }


    public Complex add(Complex n1, Complex n2){
        Complex temp = new Complex(0,0);
        temp.real = n1.real + n2.real;
        temp.imag = n1.imag + n2.imag;
        return(temp);
    }

    public Complex substract(Complex n1, Complex n2){
        Complex temp = new Complex(0,0);
        temp.real = n1.real - n2.real;
        temp.imag = n1.imag - n2.imag;
        return(temp);
    }

    public Complex multiple(Complex n1, Complex n2){
        Complex temp = new Complex(0,0);
        temp.real = n1.real*n2.real - n1.imag*n2.imag;
        temp.imag = n1.real*n2.imag + n1.imag*n2.real;
        return(temp);
    }

    public Complex divide(Complex n1, Complex n2){
        Complex temp = new Complex(0,0);
        temp.real = (n1.real*n2.real + n1.imag*n2.imag)/(n2.real*n2.real + n2.imag*n2.imag);
        temp.imag = (n1.imag*n2.real - n1.real*n2.imag)/(n2.real*n2.real + n2.imag*n2.imag);
        return(temp);
    }

    
    public boolean isReal(Complex n){
        return this.imag == 0;
    }

    public boolean isImage(Complex n){
        return this.real == 0;
    }

    public int compareTo(Complex n){
         

    }

    @Override
    public String toString(){
        return "The complex number is " + this.real + " + " + this.imag + "i";
    }

    @Override
    public boolean equals(Object n){

    }

    @Override
    public int hashCode() {
    }

    public Complex stringToComplex(String str){
    }


    
 }