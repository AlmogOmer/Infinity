package il.co.ilrd.networking;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;


public class ServerChat {
    private final ServerSocket serverSocket;

    public ServerChat(ServerSocket serverSocket) {
        this.serverSocket = serverSocket;
    }

    public void startServer() {
        try {
            while (!serverSocket.isClosed()) {
                Socket socket = serverSocket.accept();
                System.out.println("A new client has connected!");
                ClientHandlerChat clientHandler = new ClientHandlerChat(socket);
                Thread thread = new Thread(clientHandler);
                thread.start();
            }
        } catch (IOException e) {
            closeServerSocket();
        }
    }

    public void closeServerSocket() {
        try {
            if (serverSocket != null) {
                serverSocket.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(6666);
        ServerChat server = new ServerChat(serverSocket);
        server.startServer();
    }



}
