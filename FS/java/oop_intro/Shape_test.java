public class Shape_test {
    public static void main(String[] args) {
        /*Shape s1 = new Shape();
        s1.SetColor("red");
        s1.SetFilled(true);
        System.out.println(s1.toString());

        Circle c1 = new Circle(5,"blue", true);
        System.out.println(c1.GetArea());
        System.out.println(c1.GetPerimeter());
        System.out.println(c1.toString());
        
        Rectangle r1 = new Rectangle(5,5,"yellow", true);
        System.out.println(r1.GetArea());
        System.out.println(r1.GetPerimeter());
        System.out.println(r1.toString());

        Square q1 = new Square();
        System.out.println(q1.GetArea());
        System.out.println(q1.GetPerimeter());
        System.out.println(q1.toString());*/

        Shape s1 = new Circle(5.5, "RED", false); /* upcasting */
        System.out.println(s1);
        System.out.println(s1.GetArea());
        System.out.println(s1.GetPerimeter());
        System.out.println(s1.GetColor());
        /* System.out.println(s1.getRadius()); wont work, unknown operation for Shape */

        Circle c1 = (Circle) s1;/* downcasting */
        System.out.println(c1);
        System.out.println(c1.GetArea());
        System.out.println(c1.GetPerimeter());
        System.out.println(c1.GetColor());
        System.out.println(c1.GetRadius());

        /* Shape s2 = new Shape(); wont work, Shapre is an abstract class */

        Shape s3 = new Rectangle(1.0, 2.0, "RED", false);

        System.out.println(s3);
        System.out.println(s3.GetArea());
        System.out.println(s3.GetPerimeter());
        System.out.println(s3.GetColor());
        /*
          System.out.println(s3.getLength()); Wont work because s3 the pointer is of
          type Shape and it doesnt know getLength
         */

        Rectangle r1 = (Rectangle) s3;
        System.out.println(r1);
        System.out.println(r1.GetArea());
        System.out.println(r1.GetColor());
        System.out.println(r1.GetLength());

        Shape s4 = new Square(6.6);
        System.out.println(s4);
        System.out.println(s4.GetArea());
        System.out.println(s4.GetColor());
        /*  System.out.println(s4.getSide()); wont work becuase s4 is of type Shape and
        not Square */

        Rectangle r2 = (Rectangle) s4;
        System.out.println(r1);
        System.out.println(r1.GetArea());
        System.out.println(r1.GetColor());
        /* System.out.println(r1.getSide()); wont work because this function needs to know getSide function, and the object itself is rectangle and it doesnt have this function */
        System.out.println(r1.GetLength());

        Square sq1 = (Square) r2;
        System.out.println(sq1);
        System.out.println(sq1.GetArea());
        System.out.println(sq1.GetColor());
        System.out.println(sq1.GetSide());
        System.out.println(sq1.GetLength());

    }
    
}
