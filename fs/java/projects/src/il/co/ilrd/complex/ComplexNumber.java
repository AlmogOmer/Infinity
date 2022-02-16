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

    
    public boolean isReal(){
        return imag == 0;
    }

    public boolean isImag(){
        return real == 0;
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

    public static ComplexNumber parsing(String str) {
        ComplexNumber result = new ComplexNumber(0,0);
        String[] s1 = str.split(" ", 2);
        String[] s2 = s1[1].split("i", 2);

        result.real = Double.parseDouble(s1[0]);
        result.imag = Double.parseDouble(s2[0]);

        return result;

    }


    /*public static ComplexNumber parsing(String str){
        
        ComplexNumber result = new ComplexNumber(0,0);
        int i = 0;
        int startNegFlag = 0;
        int midNegFlag = 0;
        double temp1 = 0;
        double temp2 = 0;
        if(i < str.length() && str.charAt(i) == '-')
        {
            startNegFlag = 1;
            ++i;
        }
        while(i < str.length() && str.charAt(i) >= '0' && str.charAt(i) <= '9')
        {
            temp1 = temp1*10 + (double)(str.charAt(i) - '0');
            ++i;
        }

        if (i == str.length()){
            result.real = temp1;
            if(startNegFlag == 1){
                result.real *= -1;
            }
            return result;
        }
        
        else if (i < str.length() && str.charAt(i) == '+'){
            result.real = temp1;
            if(startNegFlag == 1){
                result.real *= -1;
            }
            ++i;
        }
        else if(i < str.length() && str.charAt(i) == '-')
        {
            result.real = temp1;
            if(startNegFlag == 1){
                result.real *= -1;
            }
            midNegFlag = 1;
            ++i;
        }

        else if (i < str.length() && str.charAt(i) == 'i'){
            result.imag = temp1;
            if(startNegFlag == 1){
                result.imag *= -1;
            }
            ++i;

            if (i < str.length() && str.charAt(i) == '-'){
                midNegFlag = 1;
                ++i;
            }
            else if (i < str.length() && str.charAt(i) == '+'){
                ++i;
            }
        }


        while(i < str.length() && str.charAt(i) >= '0' && str.charAt(i) <= '9')
        {
            temp2 = temp2*10 + (double)(str.charAt(i) -'0');
            ++i;
        }

        if (i < str.length() && str.charAt(i) == 'i'){
            result.imag = temp2;
            if(midNegFlag == 1){
                result.imag *= -1;
            }
        }

        else{
            result.real = temp2;
            if(midNegFlag == 1){
                result.real *= -1;
            }
        }

        return result;
    }*/

 }
