package org.tp;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

public class ClientPut {

    public static void main(String[] args) throws IOException {
        String request = "PUT /" + args[0] + " HTTP/1.1\n\n";
        try(FileInputStream is = new FileInputStream(args[0])) {
            byte[] content = new byte[is.available()];
            is.read(content);
            request += new String(content);
        }
        Socket socket = new Socket("localhost", Server.PORT);
        OutputStream outputStream = socket.getOutputStream();
        outputStream.write(request.getBytes());
        outputStream.flush();
        
        InputStream is = socket.getInputStream();
        byte[] content = new byte[is.available()];
        is.read(content);
        System.out.println(new String(content));
        socket.close();
    }

}
