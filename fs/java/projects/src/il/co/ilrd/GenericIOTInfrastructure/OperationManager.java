package il.co.ilrd.GenericIOTInfrastructure;

import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import il.co.ilrd.factory.Factory;
import il.co.ilrd.hashmap.Pair;


public class OperationManager {
    private final ExecutorService executor;
    private final IOTDBMS dbms;
    private final Factory<Command, FactoryData, String> commandFactory;

    public OperationManager(IOTDBMS dbms, Factory<Command, FactoryData, String> commandFactory) {
        this.dbms = dbms;
        executor = Executors.newCachedThreadPool();
        this.commandFactory = commandFactory;
    
    }

    public void handleRequest(String request, Responder respond) {
        String key = request.split(" ")[0];
        FactoryData factoryData = new FactoryData(request.substring(request.split(" ")[0].length()), respond, dbms);

        Callable<Void> callable = new Callable<>() {

            @Override
            public Void call() throws Exception {
                commandFactory.create(key, factoryData).run();
                return null;
            }

        };

        executor.submit(callable);

    }

    public void stop() {
        executor.shutdown();
    }
}

class CompanyRegisterCommand implements Command {
    private final Pair<String, Responder> pair;
    private final IOTDBMS dbms;

    public CompanyRegisterCommand(FactoryData factoryData) {
        pair = Pair.of(factoryData.getData(), factoryData.getResponder());
        dbms = factoryData.getDbms();

    }

    @Override
    public void run() {
        dbms.companyAdd(pair);
    }
}

class ProductRegisterCommand implements Command {
    private final Pair<String, Responder> pair;
    private final IOTDBMS dbms;

    public ProductRegisterCommand(FactoryData factoryData) {
        pair = Pair.of(factoryData.getData(), factoryData.getResponder());
        dbms = factoryData.getDbms();

    }

    @Override
    public void run() {
        dbms.productAdd(pair);
    }
}

class IOTRegisterCommand implements Command {
    private final Pair<String, Responder> pair;
    private final IOTDBMS dbms;

    public IOTRegisterCommand(FactoryData factoryData) {
        pair = Pair.of(factoryData.getData(), factoryData.getResponder());
        dbms = factoryData.getDbms();

    }

    @Override
    public void run() {
        dbms.IOTAdd(pair);
    }
}

class IOTUpdateCommand implements Command {
    private final Pair<String, Responder> pair;
    private final IOTDBMS dbms;

    public IOTUpdateCommand(FactoryData factoryData) {
        pair = Pair.of(factoryData.getData(), factoryData.getResponder());
        dbms = factoryData.getDbms();

    }

    @Override
    public void run() {
        dbms.IOTUpdate(pair);
    }
}

class PingCommand implements Command {
    private final Responder responder;

    public PingCommand(FactoryData factoryData) {
        this.responder = factoryData.getResponder();
    }

    @Override
    public void run() {
        responder.respond("pong");

    }
}
