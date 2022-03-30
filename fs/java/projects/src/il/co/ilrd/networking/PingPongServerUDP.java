package il.co.ilrd.networking;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

public class PingPongServerUDP {
    private DatagramSocket socket;
    private boolean running;
    private byte[] bufin = new byte[256];
    private byte[] bufout = {'P', 'o', 'n', 'g'};

    public PingPongServerUDP(int port) throws SocketException {
        socket = new DatagramSocket(port);
    }

    public void start() throws IOException {
        running = true;

        while (running) {
            DatagramPacket packet = new DatagramPacket(bufin, bufin.length);
            socket.receive(packet);
            
            InetAddress address = packet.getAddress();
            int port = packet.getPort();
            DatagramPacket newpacket = new DatagramPacket(bufout, bufout.length, address, port);
            String received = new String(packet.getData(), 0, packet.getLength());
            
            if (received.equals("end")) {
                running = false;
                bufout = "end".getBytes();
                newpacket = new DatagramPacket(bufout, bufout.length, address, port);
            }
            socket.send(newpacket);
        }
        socket.close();
    }

    /*public static void main(String args[]) throws IOException{
        PingPongServerUDP server = new PingPongServerUDP(4445);
        server.start();
    }*/
}
