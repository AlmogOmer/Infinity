package il.co.ilrd.iosystem;

import java.io.IOException;
import java.nio.file.*;

import il.co.ilrd.observer.Callback;
import il.co.ilrd.observer.Dispatcher;

public class FolderMonitor {
    private Dispatcher<String> dispatcher = new Dispatcher<>();
    private Path path;
    private WatchService watchService;
    private Thread watchingThread;

    public FolderMonitor(String pathFolder) throws IOException {
        watchService = FileSystems.getDefault().newWatchService();
        path = Paths.get(pathFolder);
        path.register(watchService, StandardWatchEventKinds.ENTRY_CREATE, StandardWatchEventKinds.ENTRY_DELETE,
                StandardWatchEventKinds.ENTRY_MODIFY);

    }

    public void start() {
        watchingThread = new Thread() {
            @Override
            public void run() {
                WatchKey key;
                try {
                    while ((key = watchService.take()) != null) {
                        for (WatchEvent<?> event : key.pollEvents()) {
                            if (event.kind().toString().equals("ENTRY_MODIFY")) {
                                dispatcher.notifyAllCallback(event.context().toString());
                            }
                        }
                        key.reset();
                    }
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }

        };
        watchingThread.start();

        /*
         * WatchKey key;
         * while ((key = watchService.take()) != null) {
         * for (WatchEvent<?> event : key.pollEvents()) {
         * System.out.println("Event kind:" + event.kind() + ". File affected: " +
         * event.context() + ".");
         * }
         * key.reset();
         * }
         */
    }

    public void register(Callback<String> callback) {
        dispatcher.register(callback);
    }

    public void unregister(Callback<String> callback) {
        dispatcher.unregister(callback);
    }

    public void stop() {
        if (watchingThread != null) {
            watchingThread.interrupt();
        }

        dispatcher.stopAllCallback();
    }

}
