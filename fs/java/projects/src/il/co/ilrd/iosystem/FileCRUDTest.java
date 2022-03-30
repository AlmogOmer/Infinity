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
    public void testClose() {

    }

    @Test
    public void testCreate() {
        try {
            f.create("fdfdf");
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
    }

    @Test
    public void testDelete() {

    }

    @Test
    public void testRead() {

    }

    @Test
    public void testUpdate() {

    }
}
