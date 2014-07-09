package fr.upmc.srcs.tme2;

import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import java.io.FileNotFoundException;


public class HttpRequest extends Thread{
	private Socket scom;
	
	public HttpRequest(Socket s){
		this.scom = s;
	}
	public void run (){
		try {
			this.processRequest();
		} 
		catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	private void processRequest() throws IOException{
		InputStreamLiner isl = new InputStreamLiner(this.scom.getInputStream());
		String s;
		String[] splits;
		s=isl.readLineUnix();
		System.out.println("s : "+s);
		splits=s.split(" ");
		if (splits[0].equals("GET")){
			this.processGet(s, isl);
		}
		isl.close();
	}
	
	private void processGet(String s, InputStreamLiner isl) throws IOException{
		String[] splits;
		InputStreamLiner fisl = null;
		splits = s.split(" ");
		DataOutputStream dos;
		File f;
		while ((s=isl.readLine(InputStreamLiner.UNIX)) != null){
			if(s.equals(""))
				break;
		}
		try {
			fisl = new InputStreamLiner(new FileInputStream(splits[1]));
			f = new File(splits[1]);
			dos = new DataOutputStream(this.scom.getOutputStream());
			dos.writeBytes("HTTP/1.1 200 OK\n");
			dos.writeBytes("Content-length:"+f.length()+"\n");
			dos.writeBytes("Content-type: text/html\n");
			dos.writeBytes("\n");
			

			while ((s = fisl.readLineUnix()) != null){
				s+="\n";
				dos.writeBytes(s);
			}
			
		}
		catch (FileNotFoundException e){
			System.out.println("failed");
			dos = new DataOutputStream(this.scom.getOutputStream());
			dos.writeBytes("HTTP/1.1 404 FileNotFound");
			dos.writeBytes("\n");
			dos.writeBytes("The file cannot be retrieved on the server, sorry.");
			dos.flush();

			return;
		}
		fisl.close();
	}
}
