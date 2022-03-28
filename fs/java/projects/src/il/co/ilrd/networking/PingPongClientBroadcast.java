//package il.co.ilrd.networking;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class PingPongClientBroadcast {
    public static void main(String[] args) throws IOException {
        int servers = 3;

        Scanner scan = new Scanner(System.in);
        ArrayList<Integer> ports = new ArrayList<>(servers);

        for(int i=0; i < servers; i++)  
        {   
            ports.add(scan.nextInt());
        }  
        
        PingPongClientUDP clientUDP = new PingPongClientUDP();

        for (int port : ports) {
            clientUDP.send("ping", port);
        }

            
        for (int port : ports) {
            clientUDP.send("end", port);
        }

        clientUDP.close();
        scan.close();

    }
}
