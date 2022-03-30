package il.co.ilrd.networking;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;




public class MultiprotocolServer {
    private DatagramSocket socket;
    private ServerSocket serverSocket;
    private Socket clientSocket;
    private ServiceHandler serviceHandler = new ServiceHandler();
   
    public MultiprotocolServer(int port) throws IOException{
        serverSocket = new ServerSocket(port);
        socket = new DatagramSocket(port);
    }

    public void startServer(){
        Thread UDPThread = new Thread(new Runnable() {
            @Override
            public void run() {
                System.out.println("UDPThread1");
                String massage;
                while (socket.isConnected()) {
                    System.out.println("UDPThread2");
                    byte[] bufin = new byte[256];
                    DatagramPacket packet = new DatagramPacket(bufin, bufin.length);
                    try {
                        socket.receive(packet);
                        massage = new String(packet.getData(), 0, packet.getLength());
                        UDPesponse response = new UDPesponse(packet);
                        serviceHandler.handleMassage(massage, response);

                    } catch (IOException e) {
                        socket.close();
                    }
                    }
                }
            });
        
        UDPThread.start();
    
        Thread TCPThread = new Thread(new Runnable() {
            @Override
            public void run() {
                System.out.println("TCPThread1");
                String massage;
                while (!serverSocket.isClosed()) {
                    System.out.println("TCPThread2");
                    try {
                        clientSocket = serverSocket.accept();
                        System.out.println("TCPThread3");
                        BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                        massage = in.readLine();
                        TCPResponse response = new TCPResponse(clientSocket);
                        serviceHandler.handleMassage(massage, response);

                    } catch (IOException e) {
                        closeServerSocket();
                        break;
                    }
                }
            }
        });
        
        TCPThread.start();
    
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

    interface Response{
        void response(String massage);
    }

    class TCPResponse implements Response{
        Socket clientSocket;
        public TCPResponse(Socket clientSocket){
            this.clientSocket = clientSocket;
        }

        @Override
        public void response(String message) {
            try {
                BufferedWriter bufferedWriter= new BufferedWriter(new OutputStreamWriter(clientSocket.getOutputStream()));
                bufferedWriter.write(message);
                bufferedWriter.newLine();
                bufferedWriter.flush();
            } catch (IOException e) {
                e.printStackTrace();
            }
            
        }
        

    }

    class UDPesponse implements Response{
        DatagramPacket packet;
        public UDPesponse(DatagramPacket packet){
            this.packet = packet;
        }

        @Override
        public void response(String message) {
            try {
                byte[] bufout = message.getBytes();
                InetAddress address = packet.getAddress();
                int port = packet.getPort();
                DatagramPacket newpacket = new DatagramPacket(bufout, bufout.length, address, port);
                socket.send(newpacket);
            } catch (IOException e) {
                e.printStackTrace();
            }
            
        }
        

    }

    interface Service{
        public void sendResponse(String massage, Response response);
    }

    class ServicePingPong implements Service{
        @Override
        public void sendResponse(String massage, Response response) {
            response.response("pong");
        }

    }

    class ServiceChat implements Service{
        
        @Override
        public void sendResponse(String massage, Response response) {
            //response.response(massage); 
        }
    }

    class ServiceHandler{
        private HashMap<String,Service> serviceMap = new HashMap<>();

        public ServiceHandler(){
            serviceMap.put("chat", new ServicePingPong());
            serviceMap.put("ping", new ServiceChat());
        }

        public void handleMassage(String massage, Response response) throws IOException{
            String arr[] = massage.split(" ", 2);
            String key = arr[0]; 
            String restMassage = arr[1];

            serviceMap.get(key).sendResponse(restMassage, response);


        }

    }

    public static void main(String args[]) throws IOException{
        MultiprotocolServer server = new MultiprotocolServer(4445);
        server.startServer();
    }


    
}
