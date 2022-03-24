//package il.co.ilrd.networking;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;

public class PingPongClientUDP {
    private DatagramSocket socket;
    private InetAddress address;
    private byte[] buf;

    public PingPongClientUDP() throws SocketException, UnknownHostException {
        socket = new DatagramSocket();
        address = InetAddress.getLocalHost();
    }

    public String sendEcho(String msg) throws IOException {
        buf = msg.getBytes();
        DatagramPacket packet = new DatagramPacket(buf, buf.length, address, 4445);
        socket.send(packet);
        packet = new DatagramPacket(buf, buf.length);
        socket.receive(packet);
        String received = new String(packet.getData(), 0, packet.getLength());
        return received;
    }

    public void close() {
        socket.close();
    }    
    
    /*public static void main(String args[]) throws IOException{
        PingPongClientUDP client = new PingPongClientUDP();
        String response = client.sendEcho("ping");
        System.out.println(response);
        client.sendEcho("end");
        client.close();

    }*/
}

