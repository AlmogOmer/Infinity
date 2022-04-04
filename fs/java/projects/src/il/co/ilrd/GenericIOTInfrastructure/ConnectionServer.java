package il.co.ilrd.GenericIOTInfrastructure;

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

public class ConnectionServer {
    private DatagramSocket datagramSocket;
    private ServerSocket serverSocket;
    private Socket clientSocket;
    private boolean runningUDP = false;
    OperationManager op;

    public ConnectionServer(int port, String path) throws IOException {
        serverSocket = new ServerSocket(port);
        datagramSocket = new DatagramSocket(port);
        op = new OperationManager(path);
    }

    public void start() {
        runningUDP = true;
        Thread UDPThread = new Thread(new Runnable() {
            @Override
            public void run() {
                String massage;
                while (runningUDP) {
                    byte[] bufin = new byte[256];
                    DatagramPacket packet = new DatagramPacket(bufin, bufin.length);
                    try {
                        datagramSocket.receive(packet);
                        massage = new String(packet.getData(), 0, packet.getLength());
                        UDPesponder respond = new UDPesponder(packet, datagramSocket);
                        op.handleRequest(massage, respond);

                    } catch (IOException e) {
                        datagramSocket.close();
                    }
                }
            }
        });

        UDPThread.start();

        Thread TCPThread = new Thread(new Runnable() {
            @Override
            public void run() {
                String massage;
                while (!serverSocket.isClosed()) {
                    try {
                        clientSocket = serverSocket.accept();
                        BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                        massage = in.readLine();
                        TCPResponder respond = new TCPResponder(clientSocket);
                        op.handleRequest(massage, respond);

                    } catch (IOException e) {
                        try {
                            serverSocket.close();
                        } catch (IOException e1) {
                            e1.printStackTrace();
                        }
                        break;
                    }
                }
            }
        });

        TCPThread.start();

    }

    public void stop() {
        try {
            if (datagramSocket != null) {
                datagramSocket.close();
            }
            if (serverSocket != null) {
                serverSocket.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

class TCPResponder implements Responder {
    Socket clientSocket;

    public TCPResponder(Socket clientSocket) {
        this.clientSocket = clientSocket;
    }

    @Override
    public void respond(String feedback) {
        try {
            BufferedWriter bufferedWriter = new BufferedWriter(
                    new OutputStreamWriter(clientSocket.getOutputStream()));
            bufferedWriter.write(feedback);
            bufferedWriter.newLine();
            bufferedWriter.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

}

class UDPesponder implements Responder {
    DatagramPacket packet;
    DatagramSocket datagramSocket;

    public UDPesponder(DatagramPacket packet, DatagramSocket datagramSocket) {
        this.packet = packet;
        this.datagramSocket = datagramSocket;
    }

    @Override
    public void respond(String feedback) {
        try {
            byte[] bufout = feedback.getBytes();
            InetAddress address = packet.getAddress();
            int port = packet.getPort();
            DatagramPacket newpacket = new DatagramPacket(bufout, bufout.length, address, port);
            datagramSocket.send(newpacket);
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

}