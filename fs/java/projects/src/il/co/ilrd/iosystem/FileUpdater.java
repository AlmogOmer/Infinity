package il.co.ilrd.iosystem;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;
import java.util.function.Consumer;

import il.co.ilrd.observer.Callback;

public class FileUpdater {
    private Path originalPath;
    private Path BUPath;
    private FileCRUD file;
    private Callback<String> callback;

    public FileUpdater(String originalPath, String BUPath) throws IOException {
        try (FileCRUD f = new FileCRUD(originalPath)) {

        } catch (Exception e) {
            e.printStackTrace();
        }

        file = new FileCRUD(BUPath);

        this.originalPath = Paths.get(originalPath);
        this.BUPath = Paths.get(BUPath);

        Consumer<String> update = new Consumer<String>() {
            @Override
            public void accept(String t) {
                update(t);
            }
        };

        Runnable stopService = new Runnable() {
            @Override
            public void run() {
                stop();
            }
        };

        callback = new Callback<>(update, stopService);

        update(this.originalPath.toFile().getName());

    }

    public void update(String str) {
        try {
            if (!str.equals(this.originalPath.toFile().getName())) {
                return;
            }
            List<String> lines = Files.readAllLines(this.originalPath);
            int busize = Files.readAllLines(this.BUPath).size();
            if (lines.size() > busize) {
                for (int i = 0; i < busize; ++i) {
                    file.update(i, lines.get(i));
                }
                for (int i = busize; i < lines.size(); ++i) {
                    file.create(lines.get(i));
                }
            } else if (lines.size() < busize) {

                for (int i = 0; i < lines.size(); ++i) {
                    if (!file.read(i).equals(lines.get(i))) {
                        file.delete(i);
                        --i;
                    }
                }
            } else {
                for (int i = 0; i < lines.size(); ++i) {
                    if (!file.read(i).equals(lines.get(i))) {
                        file.update(i, lines.get(i));
                    }
                }

            }
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public void stop() {
        System.out.println("backup service was stopped");
    }

    public void register(FolderMonitor foldermonitor) {
        foldermonitor.register(callback);
    }

    public void unregister(FolderMonitor foldermonitor) {
        foldermonitor.unregister(callback);
    }
}
