package org.tp;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {
    
    static final int PORT = 2020;
    
    public static void main(String[] args) throws IOException {
        ServerSocket server = new ServerSocket(PORT);
        System.err.println("Démarrage du serveur sur le port " + PORT);
        while(true) {
            final Socket s = server.accept();
            // Creer thread
            new Thread(new Runnable() {
                
                @Override
                public void run() {
                    try {
                        new HttpRequest().process(s);
                    } catch (IOException e) {
                        e.printStackTrace();
                    } finally {
                        try {
                            s.close();
                        } catch (IOException e) {}
                    }
                }
            }).start();
        }
        
    }

}
