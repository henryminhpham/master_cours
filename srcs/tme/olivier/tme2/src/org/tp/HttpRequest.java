package org.tp;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

public class HttpRequest {

    final private FileWrapper wrapper = new FileWrapper();

    public void process(Socket s) throws IOException {
        InputStream is = s.getInputStream();
        byte[] content = new byte[is.available()];
        is.read(content);
        String request = new String(content);
        String result;
        if (request.startsWith("GET")) {
            result = processGet(request);
        } else if (request.startsWith("PUT")) {
            result = processPut(request);
        } else {
            result = "HTTP/1.1 403 Access forbidden\n\n";
        }
        OutputStream outputStream = s.getOutputStream();
        outputStream.write(result.getBytes());
        outputStream.flush();
    }

    public String processGet(String s) {        
        String URI = getURI(s);
        try {
            if (URI.equals("")) {
                System.err.println("Requête GET effectuée sur index.html");
                return wrapper.read("context/index.html");
            }
            System.err.println("Requête GET effectuée sur " + URI);
            return wrapper.read("context/" + URI);
        } catch (IOException e) {
            System.err.println("Le fichier " + URI + " n'existe pas.");
            return "HTTP/1.1 404 Not Found\n\n"; // TODO : Mettre une vraie erreur 404
        }
    }

    public String processPut(String s) {
        String uri = getURI(s);
        String realURI = "context/" + uri;
        System.err.println("Requête PUT effectuée sur " + uri);
        try {
            String realContent = s.substring(s.indexOf("\n\n") + 2, s.length());
            wrapper.write(realURI, realContent);
        } catch (IOException e) {
            System.err.println("Impossible d'écrire dans le fichier.");
            return "HTTP/1.1 500 Server Internal Error\n\n";
        }
        return "HTTP/1.1 200 OK\n\n";
    }
    
    private String getURI(String s) {
        return s.substring(5, s.indexOf("HTTP") - 1);
    }

}
