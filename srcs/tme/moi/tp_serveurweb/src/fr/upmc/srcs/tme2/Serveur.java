package fr.upmc.srcs.tme2;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;


public class Serveur {
	public static void main (String[] args){
		ServerSocket sc = null;
		try {
			sc = new ServerSocket(2015);
			Socket scom = sc.accept();
			HttpRequest req = new HttpRequest(scom);
			req.start();
		}
		catch (IOException e){
			e.printStackTrace();
		}
		finally{
			try {
				sc.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
}
