//package il.co.ilrd.networking;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.MulticastSocket;
import java.net.NetworkInterface;
import java.nio.charset.StandardCharsets;

public class PingPongClientBroadcast {
    public static void main(String[] args) throws IOException {
        String msg = "ping";
        InetAddress mcastaddr = InetAddress.getByName("192.168.1.255");
        InetSocketAddress group = new InetSocketAddress(mcastaddr, 6789);
        NetworkInterface netIf = NetworkInterface.getByName("bge0");
        MulticastSocket s = new MulticastSocket(6789);

        s.joinGroup(new InetSocketAddress(mcastaddr, 0), netIf);
        byte[] msgBytes = msg.getBytes(StandardCharsets.UTF_8);
        DatagramPacket hi = new DatagramPacket(msgBytes, msgBytes.length, group);
        s.send(hi);

        // get their responses!
        byte[] buf = new byte[1000];
        DatagramPacket recv = new DatagramPacket(buf, buf.length);
        s.receive(recv);
        
        s.leaveGroup(group, netIf);
        
    }

   
}
