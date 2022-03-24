package il.co.ilrd.networking;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;

public class DownloadWebPage {
    public static void Download(String webpage) throws IOException
    {
        // Create URL object
        URL url = new URL(webpage);
        BufferedReader reader = new BufferedReader(new InputStreamReader(url.openStream()));

        // Enter filename in which you want to download
        BufferedWriter writer = new BufferedWriter(new FileWriter("Download.html"));
            
        // read each line from stream till end
        String line;
        while ((line = reader.readLine()) != null) {
            writer.write(line);
        }

        reader.close();
        writer.close();
        System.out.println("Successfully Downloaded.");
    }
  
    public static void main(String args[]) throws IOException{
        URL oracle = new URL("https://en.wikipedia.org");
        BufferedReader in = new BufferedReader(new InputStreamReader(oracle.openStream()));

        String inputLine;
        while ((inputLine = in.readLine()) != null)
            System.out.println(inputLine);
        in.close();

        /*String url = "https://en.wikipedia.org";
        try {
            Download(url);
        } catch (IOException e) {
            e.printStackTrace();
        }*/
    }
}

