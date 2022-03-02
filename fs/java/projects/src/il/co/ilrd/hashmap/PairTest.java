package il.co.ilrd.hashmap;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.Comparator;

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
        class TestComparator<T extends Comparable<T>> implements Comparator<T> {
            @Override
            public int compare(T obj1, T obj2) {
                return obj1.compareTo(obj2);

            }
        }
        Integer[] array = {1,2,3,4,5,6,7,8,9,10};
        Integer[] array2 = {8,96,3,14,75,6,7,0,9,10};
        Pair<Integer,Integer> p4 = Pair.of(1, 10);
        Pair<Integer,Integer> p5 = Pair.of(0, 96);
        
        assertTrue(p4.equals(Pair.minMax(array,new TestComparator<>())));
        assertTrue(p5.equals(Pair.minMax(array2,new TestComparator<>())));

    }

    @Test
    void testMinMax2() {
        Integer[] array = {1,2,3,4,5,6,7,8,9,10};
        Integer[] array2 = {8,96,3,14,75,6,7,0,9,10};
        Pair<Integer,Integer> p4 = Pair.of(1, 10);
        Pair<Integer,Integer> p5 = Pair.of(0, 96);
        
        assertTrue(p4.equals(Pair.minMax(array)));
        assertTrue(p5.equals(Pair.minMax(array2)));

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
