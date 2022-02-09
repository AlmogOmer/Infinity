public class Square extends Rectangle {
    
    public Square()
    {

    }

    public Square(double side)
    {
        width = side;
        length = side;
    }

    public Square(double side, String mycolor, boolean myfilled)
    {
        width = side;
        length = side;
        color = mycolor;
        filled = myfilled;
    }

    public double GetSide()
    {
        return this.width;
    }

    public void SetSide(double myside)
    {
        this.width = myside;
        this.length = myside;
    }
    @Override
    public void SetLength(double mylength)
    {
        SetSide(mylength);
    }

    @Override
    public void SetWidth(double mywidth)
    {
        SetSide(mywidth);
    }

    @Override
    public String toString()
    {
        return "A Square with side = " + this.width +  ",which is a subclass of " + super.toString();
    }

}