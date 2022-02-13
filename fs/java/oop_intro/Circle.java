public class Circle extends Shape {
    double radius;

    public Circle()
    {
        radius = 1.0;
    }

    public Circle(double myradius)
    {
        radius = myradius;
    }

    public Circle(double myradius,String mycolor, boolean myfilled)
    {
        radius = myradius;
        color = mycolor;
        filled = myfilled;
    }

    public double GetRadius()
    {
        return this.radius;
    }

    public void SetRadius(double myradius)
    {
        this.radius = myradius;
    }

    public double GetArea()
    {
        return this.radius * this.radius * Math.PI; 
    }

    public double GetPerimeter()
    {
        return 2 * this.radius * Math.PI;
    }

    @Override
    public String toString()
    {
        return "A Circle with radius = " + this.radius + " ,which is a subclass of " + super.toString();
    }

    
}
