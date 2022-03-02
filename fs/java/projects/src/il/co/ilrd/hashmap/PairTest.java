package il.co.ilrd.hashmap;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.Test;

public class PairTest {
    Pair<Integer,Integer> p1 = Pair.of(5, 3);
    Pair<Integer,Integer> p2 = Pair.of(5, 3); 
    Pair<Integer,Integer> p3 = Pair.of(15,13); 
    

    @Test
    void testEquals() {
        assertTrue(p1.equals(p2));
    }

    @Test
    void testGetKey() {
        assertEquals(5,p1.getKey());
        assertEquals(5,p2.getKey());
        assertEquals(15,p3.getKey());

    }

    @Test
    void testGetValue() {
        assertEquals(3,p1.getValue());
        assertEquals(3,p2.getValue());
        assertEquals(13,p3.getValue());

    }

    @Test
    void testHashCode() {
        assertEquals(p2.hashCode(),p1.hashCode());
    }

    @Test
    void testMinMax() {

    }

    @Test
    void testMinMax2() {

    }

    @Test
    void testSetKey() {
        assertEquals(5,p1.setKey(8));
        assertEquals(5,p2.setKey(8));
        assertEquals(15,p3.setKey(18));

    }

    @Test
    void testSetValue() {
        assertEquals(3,p1.setValue(7));
        assertEquals(3,p2.setValue(7));
        assertEquals(13,p3.setValue(17));

    }

    @Test
    void testSwap() {
        Pair<Integer,Integer> p4 = Pair.of(3, 5);
        assertTrue(p4.equals(Pair.swap(p1)));
    }

    @Test
    void testToString() {
        assertEquals("(15,13)",p3.toString());
    }
}
