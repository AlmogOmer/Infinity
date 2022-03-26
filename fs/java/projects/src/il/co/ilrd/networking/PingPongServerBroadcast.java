package il.co.ilrd.networking;

import java.io.IOException;
import java.util.Scanner;

public class PingPongServerBroadcast {
    public static void main(String[] args) throws IOException {
        Scanner scan = new Scanner(System.in);
        PingPongServerUDP server = new PingPongServerUDP(scan.nextInt());    
        server.start();
        scan.close();
    }
}
