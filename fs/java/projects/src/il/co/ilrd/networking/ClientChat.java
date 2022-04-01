/*package il.co.ilrd.networking;*/

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

import java.net.Socket;
import java.util.Scanner;

public class ClientChat {
    private Socket socket;
    private BufferedReader bufferedReader;
    private BufferedWriter bufferedWriter;
    private String username;

    public ClientChat(Socket socket, String username) {
        try {
            this.socket = socket;
            this.username = username;
            this.bufferedReader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            this.bufferedWriter = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        } catch (IOException e) {
            closeEverything(socket, bufferedReader, bufferedWriter);
        }
    }

    public void sendMessage() {
        /*
         * try (Scanner scanner = new Scanner(System.in)) {
         * // Initially send the username of the client.
         * bufferedWriter.write(username);
         * bufferedWriter.newLine();
         * bufferedWriter.flush();
         */

        while (socket.isConnected()) {
            String messageToSend = "hello";// scanner.nextLine();
            try {
                bufferedWriter.write(username + ": " + messageToSend);
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
            try {
                bufferedWriter.newLine();
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
            try {
                bufferedWriter.flush();
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }

        /*
         * } catch (IOException e) {
         * closeEverything(socket, bufferedReader, bufferedWriter);
         * }
         */
    }

    public void listenForMessage() {
        new Thread(new Runnable() {
            @Override
            public void run() {
                String msgFromGroupChat;
                while (socket.isConnected()) {
                    try {

                        msgFromGroupChat = bufferedReader.readLine();
                        System.out.println(msgFromGroupChat);
                    } catch (IOException e) {

                        closeEverything(socket, bufferedReader, bufferedWriter);
                    }
                }
            }
        }).start();
    }

    public void closeEverything(Socket socket, BufferedReader bufferedReader, BufferedWriter bufferedWriter) {
        try {
            if (bufferedReader != null) {
                bufferedReader.close();
            }
            if (bufferedWriter != null) {
                bufferedWriter.close();
            }
            if (socket != null) {
                socket.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) throws IOException {

        /*
         * try (Scanner scanner = new Scanner(System.in)) {
         * System.out.print("Enter your username for the group chat: ");
         * String username = scanner.nextLine();
         * 
         * Socket socket = new Socket("localhost", 4445);
         * ClientChat client = new ClientChat(socket, username);
         * 
         * client.listenForMessage();
         * client.sendMessage();
         * }
         */

        Socket socket = new Socket("localhost", 4445);
        ClientChat client = new ClientChat(socket, "almog");

        client.listenForMessage();
        client.sendMessage();
    }
}
