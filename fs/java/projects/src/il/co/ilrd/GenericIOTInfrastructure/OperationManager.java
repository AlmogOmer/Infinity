package il.co.ilrd.GenericIOTInfrastructure;

import java.io.File;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;
import java.util.concurrent.Callable;

import il.co.ilrd.factory.Factory;
import il.co.ilrd.hashmap.Pair;
import il.co.ilrd.iosystem.FileCRUD;
import il.co.ilrd.threadpool.ThreadPoolIMP;

public class OperationManager {
    private final Factory<Command, Pair<String, Responder>, String> commandFactory = new Factory<>();
    private final ThreadPoolIMP threadPool = new ThreadPoolIMP(5);
    private String databasePath;

    public OperationManager(String path) {
        databasePath = path;
        commandFactory.add("CompanyRegister", (str) -> new CompanyRegisterCommand(str));
        commandFactory.add("ProductRegister", (str) -> new ProductRegisterCommand(str));
        commandFactory.add("IOTRegister", (str) -> new IOTRegisterCommand(str));
        commandFactory.add("IOTUpdate", (str) -> new IOTUpdateCommand(str));
    }

    public void handleRequest(String request, Responder respond) {
        String arr[] = request.split(" ", 2);
        String key = arr[0];
        String data = databasePath + " " + arr[1];
        System.out.println(key + " " + data);
        Pair<String, Responder> pair = Pair.of(data, respond);

        Callable<Void> callable = new Callable<>() {

            @Override
            public Void call() throws Exception {
                commandFactory.create(key, pair).run();
                return null;
            }

        };

        threadPool.submit(callable);

    }
}

class CompanyRegisterCommand implements Command {
    Pair<String, Responder> pair;

    public CompanyRegisterCommand(Pair<String, Responder> pair) {
        this.pair = pair;
    }

    @Override
    public void run() {
        String arr[] = pair.getKey().split(" ", 3);
        String path = arr[0];
        String folderName = arr[1];
        System.out.println(path + " " + folderName);
        boolean ret = true;
        File companyoFolder = new File(path + "/" + folderName);

        if (!companyoFolder.exists()) {
            ret = companyoFolder.mkdir();

        }

        pair.getValue().respond(ret ? "company registration completed" : "company registration failed");

    }
}

class ProductRegisterCommand implements Command {
    Pair<String, Responder> pair;

    public ProductRegisterCommand(Pair<String, Responder> pair) {
        this.pair = pair;
    }

    @Override
    public void run() {
        String arr[] = pair.getKey().split(" ", 4);
        String path = arr[0];
        String folderName = arr[1];
        String fileName = arr[2];
        String filePath = path + "/" + folderName + "/" + fileName;
        boolean ret = true;
        File companyoFolder = new File(path + "/" + folderName);

        ret = companyoFolder.exists();
        if (ret) {
            try (FileCRUD fileCRUD = new FileCRUD(filePath)) {
                pair.getValue().respond("product registration completed");
            } catch (Exception e) {
                pair.getValue().respond("product registration failed");
                e.printStackTrace();
            }

        } else {
            pair.getValue().respond("product registration failed - no such company");
        }

    }
}

class IOTRegisterCommand implements Command {
    Pair<String, Responder> pair;

    public IOTRegisterCommand(Pair<String, Responder> pair) {
        this.pair = pair;
    }

    @Override
    public void run() {
        String arr[] = pair.getKey().split(" ", 5);
        String path = arr[0];
        String folderName = arr[1];
        String fileName = arr[2];
        String IOTName = arr[3];
        String filePath = path + "/" + folderName + "/" + fileName;
        boolean ret = true;
        File product = new File(filePath);

        ret = product.exists();
        if (ret) {
            try (FileCRUD fileCRUD = new FileCRUD(filePath)) {
                fileCRUD.create(IOTName);
                pair.getValue().respond("IOT registration completed");
            } catch (Exception e) {
                pair.getValue().respond("IOT registration failed");
                e.printStackTrace();
            }
        }

        else {
            pair.getValue().respond("IOT registration failed - no such product");
        }

    }
}

class IOTUpdateCommand implements Command {
    Pair<String, Responder> pair;

    public IOTUpdateCommand(Pair<String, Responder> pair) {
        this.pair = pair;
    }

    @Override
    public void run() {
        String arr[] = pair.getKey().split(" ", 5);
        String path = arr[0];
        String folderName = arr[1];
        String fileName = arr[2];
        String IOTName = arr[3];
        String update = arr[4];
        String filePath = path + "/" + folderName + "/" + fileName;
        boolean ret = true;
        File product = new File(filePath);

        ret = product.exists();
        if (ret) {
            try (FileCRUD fileCRUD = new FileCRUD(filePath)) {
                List<String> lines = Files.readAllLines(Paths.get(filePath));

                for (int i = 0; i < lines.size(); ++i) {
                    if (lines.get(i).split(" ")[0].equals(IOTName)) {
                        fileCRUD.update(i, IOTName + " " + update);
                    }
                }
                pair.getValue().respond("IOT update completed");
            } catch (Exception e) {
                pair.getValue().respond("IOT update failed");
                e.printStackTrace();
            }
        }

        else {
            pair.getValue().respond("IOT update failed - no such IOT");
        }

    }
}
