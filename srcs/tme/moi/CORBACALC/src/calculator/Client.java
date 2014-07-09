package calculator;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

import org.omg.CORBA.ORB;
import org.omg.CORBA.Object;

import calculator.serv_calcPackage.ZeroDiv;

public class Client {

	public static void main(String[] args) throws IOException {
		ORB orb = ORB.init(args, null); /** Initialisation de l'ORB. */
		/** Récupération IOR et construction de la référence Corba **/
		org.omg.CORBA.Object obj = restore("compte.ior", orb); /** construction du mandataire **/
		serv_calc calc = serv_calcHelper.narrow(obj);
		/** utilisation de compte **/
		try {
			System.out.println("Resultat : " + calc.div(1, 0));
		} catch (ZeroDiv e) {
			// TODO Auto-generated catch block
			System.out.println("Division par zero !!");
		} 
	}

	private static Object restore(String string, ORB orb) throws IOException {
		BufferedReader br = new BufferedReader(new FileReader(string)); 
		String ior = br.readLine(); // récupère l’ior enregistrée dans le fichier br.close(); // ferme le flux
		return orb.string_to_object(ior); // convertit la chaîne en object CORBA
	}
}
