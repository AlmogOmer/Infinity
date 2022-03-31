package il.co.ilrd.iosystem;

import java.io.IOException;

public class FolderMonitorTest {
    public static void main(String[] args) {
        try {
            FolderMonitor fm = new FolderMonitor(
                    "/Users/almogomer/Desktop/infinity/almog-omer/fs/java/projects/src/il/co/ilrd/iosystem/dir");
            FileUpdater bf = new FileUpdater(
                    "/Users/almogomer/Desktop/infinity/almog-omer/fs/java/projects/src/il/co/ilrd/iosystem/dir/hello1.txt",
                    "/Users/almogomer/Desktop/infinity/almog-omer/fs/java/projects/src/il/co/ilrd/iosystem/dir/buf1.txt");
            bf.register(fm);
            fm.start();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

}
