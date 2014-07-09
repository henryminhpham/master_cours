package calculator;


import java.io.IOException;

import org.omg.CORBA.ORB;

public class Client_nommage {

	public static void main(String[] args) throws IOException {
		ORB orb = ORB.init(args, null); /** Initialisation de l'ORB. */
		
		
		/** Récupération IOR et construction de la référence Corba **/
		String url = "corbaname::localhost:3456#Bob";
		
		
		org.omg.CORBA.Object obj = orb.string_to_object(url); 
		
		/*En java on ne peut pas caster directement l'objet CORBA en serv_calc donc on utilise le Helper*/
		serv_calc calc = serv_calcHelper.narrow(obj);
		
		/** utilisation de compte **/
		
		System.out.println("Resultat : " + calc.add(1, 0));
		
	}
}
