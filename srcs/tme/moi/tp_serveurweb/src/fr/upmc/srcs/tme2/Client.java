package fr.upmc.srcs.tme2;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.io.PrintWriter;


public class Client {
	public static void main(String[] args) throws IOException, InterruptedException {
		Socket scom = null;
		PrintWriter out;
		InputStream is;
		InputStreamLiner fisl;
		InputStreamLiner sisl;
		String s, res;
		String[] splits;
		int datanb, nb=0;
		byte[] buf;
		try {
		     scom = new Socket(InetAddress.getLocalHost(),2015);
		     out = new PrintWriter(scom.getOutputStream());
		     fisl = new InputStreamLiner(new FileInputStream("data/req.txt"));
		     while ((s = fisl.readLineUnix()) != null){
		    	 System.out.println(s);
			     out.println(s);
		     }
		     out.println("\n");
		     out.flush();
		     
		     
		     sisl = new InputStreamLiner(scom.getInputStream());
		     is = scom.getInputStream();
		     s = sisl.readLineUnix();
		     splits = s.split(" ");
		     
		     
		     if(splits[1].equals("200")){
		    	 System.out.println(splits[1]+" : "+"Success");
		    	 s = sisl.readLineUnix();
		    	 splits = s.split(":");
		    	 datanb = Integer.parseInt(splits[1]);
		    	 while((s = sisl.readLineUnix()) != null){
		    		 if (s.equals("")){
		    			 break;
		    		 }
		    	 }
		    	 buf = new byte[datanb];
		    	 while ((nb += is.read(buf, nb, datanb-nb))>0){
		    		 if(nb == datanb)
		    			 break;
		    	 }
		    	 res = new String(buf);
		    	 System.out.println("res : "+res);
		     }
		     else{
		    	 System.out.println("Error on server");
		    	 System.out.println(splits[1]+" "+splits[2]);
		     }
		     out.close();
	         scom.close();
		}
		catch (UnknownHostException e) {
			e.printStackTrace();
		}
		catch (FileNotFoundException e) {
			e.printStackTrace();
			System.out.println("Request not found!");
		}
	}
}
