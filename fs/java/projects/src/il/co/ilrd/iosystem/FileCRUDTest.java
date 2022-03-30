package il.co.ilrd.iosystem;

import static org.junit.jupiter.api.Assertions.assertEquals;

import java.io.IOException;

import org.junit.Before;
import org.junit.Test;

public class FileCRUDTest {
    FileCRUD f;
@Before
public void before()
{
    try {
        f = new FileCRUD("/Users/almogomer/Desktop/infinity/almog-omer/fs/java/projects/a.txt");
    } catch (IOException e) {
        // TODO Auto-generated catch block
        e.printStackTrace();
    }
    
}
    @Test
    public void test() {
        try {
            f.create("fdfdf");
            f.create("dddd");
            f.create("eee");
            f.create("yyy");
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        try {
            assertEquals(f.read(0), "fdfdf");
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        try {
            f.delete(2);
            assertEquals(f.read(2), "yyy");
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        try {
            f.update(1, "ggg");
            assertEquals(f.read(1), "ggg");
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        
    }

    


}
