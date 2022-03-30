package il.co.ilrd.iosystem;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;

public class FileCRUD implements CRUD<Integer, String> {
    private final List<String> lines;
    private final Path path;

    public FileCRUD(String path) throws IOException {
        createFileIfNotFound(path);
        this.path = new File(path).toPath();
        lines = Files.readAllLines(this.path);
    }

    @Override
    public void close() throws Exception {
        
    }

    @Override
    public Integer create(String data) throws IOException {
        lines.add(data);
        Files.write(path, lines); 
        return lines.size()-1;
    }

    @Override
    public String read(Integer key) throws IOException {
        return lines.get(key);
    }

    @Override
    public void update(Integer key, String data) throws IOException {
        lines.set(key, data);
        Files.write(path, lines); 
    }

    @Override
    public void delete(Integer key) throws IOException {
        int idx = key;
        lines.remove(idx);
        Files.write(path, lines); 

    }
    private void createFileIfNotFound(String s)
    {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(s))) {
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
