package complex;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.Before;
import org.junit.Test;

public class ComplexTest {
    ComplexNumber n1;
    ComplexNumber n2; 
    
    @Before
    public void before(){
        n1 = ComplexNumber.createFromReal(3);
        n1.setImg(4);

        n2 = ComplexNumber.createFromReal(7);
        n2.setImg(2);
    }
    
    @Test
    public void testAdd() {
        ComplexNumber addResult = ComplexNumber.add(n1, n2);
        assertEquals(10, addResult.getReal());
        assertEquals(6, addResult.getImg());
    }

    @Test
    public void testCompareTo() {
        assertTrue(0 > n1.compareTo(n2));
    }

    @Test
    public void testEquals() {
        assertFalse(n1.equals(n2));
    }

    @Test
    public void testHashCode() {
        assertEquals(33031105, n1.hashCode());
        assertEquals(1835969, n2.hashCode());
    }

    @Test
    public void testIsImag() {
        assertFalse(n1.isImag(n1));
        assertFalse(n2.isImag(n2));
    }

    @Test
    public void testIsReal() {
        assertFalse(n1.isReal(n1));
        assertFalse(n2.isReal(n2));

    }

    @Test
    public void testMul() {
        ComplexNumber mulResult = ComplexNumber.mul(n1, n2);
        assertEquals(13, mulResult.getReal());
        assertEquals(34, mulResult.getImg());

    }

    @Test
    public void testParsing() {
        ComplexNumber parsingResult = ComplexNumber.parsing("3+8i");
        assertEquals(3, parsingResult.getReal());
        assertEquals(8, parsingResult.getImg());

    }

    @Test
    public void testSetReal() {
        n1.setReal(1);
        assertEquals(1, n1.getReal());

    }

    @Test
    public void testSub() {
        ComplexNumber subResult = ComplexNumber.sub(n1, n2);
        assertEquals(-4, subResult.getReal());
        assertEquals(2, subResult.getImg());

    }

    @Test
    public void testToString() {
        System.out.println(n1.toString());
        System.out.println(n2.toString());

    }
}
