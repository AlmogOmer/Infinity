abstract public class Shape{
    String color;
    boolean filled;

    public Shape()
    {
        color = "green";
        filled = true;
    }

    public Shape(String mycolor, boolean myfilled)
    {
        color = mycolor;
        filled = myfilled;
    }

    public String GetColor()
    {
        return this.color;
    }

    public void SetColor(String mycolor)
    {
        this.color = mycolor;
    }

    public boolean GetFilled()
    {
        return this.filled;
    }

    public void SetFilled(boolean myfilled)
    {
        this.filled = myfilled;
    }

    @Override
    public String toString()
    {
        String filled_value;

        if (GetFilled()){
            filled_value = "filled";
        }

        else{
            filled_value = "not filled";
        }

        return "A Shape with color of " + this.color + " and " + filled_value;
    }

    abstract public double GetArea();

    abstract public double GetPerimeter();


} 