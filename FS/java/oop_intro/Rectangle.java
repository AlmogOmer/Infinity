public class Rectangle extends Shape{
    double width;
    double length;

    public Rectangle()
    {
        width = 1.0;
        length = 1.0;
    }

    public Rectangle(double mywidth, double mylength)
    {
        width = mywidth;
        length = mylength;
    }

    public Rectangle(double mywidth, double mylength, String mycolor, boolean myfilled)
    {
        width = mywidth;
        length = mylength;
        color = mycolor;
        filled = myfilled;
    }

    public double GetWidth()
    {
        return this.width;
    }

    public double GetLength()
    {
        return this.length;
    }

    public void SetWidth(double mywidth)
    {
        this.width = mywidth;
    }

    public void SetLength(double mylength)
    {
        this.length = mylength;
    }

    public double GetArea()
    {
        return this.length * this.width; 
    }

    public double GetPerimeter()
    {
        return 2 * this.length + 2 * this.width;
    }

    @Override
    public String toString()
    {
        return "A Rectangular with width = " + this.width + " and length = " + this.length + ",which is a subclass of " + super.toString();
    }

    
}
