package il.co.ilrd.iosystem;

import java.io.IOException;
import java.nio.file.*;

public class FolderMonitor {
    Path path;

    public FolderMonitor(String path) throws IOException, InterruptedException{
        WatchService watchService = FileSystems.getDefault().newWatchService();
        this.path = Paths.get(path);
        this.path.register(watchService,StandardWatchEventKinds.ENTRY_CREATE,StandardWatchEventKinds.ENTRY_DELETE,StandardWatchEventKinds.ENTRY_MODIFY);

        WatchKey key;
        while ((key = watchService.take()) != null) {
            for (WatchEvent<?> event : key.pollEvents()) {
                System.out.println("Event kind:" + event.kind() + ". File affected: " + event.context() + ".");
            }
            key.reset();
        }
    }

    public static void main(String[] args) {
        try {
            FolderMonitor m = new FolderMonitor("/Users/almogomer/Desktop/infinity/almog-omer/fs/java/projects/monitorTest");
        } catch (IOException | InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
   
    
}
