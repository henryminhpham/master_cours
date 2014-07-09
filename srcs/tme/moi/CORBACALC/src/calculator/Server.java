package calculator;

import java.io.FileWriter;
import java.io.IOException;

import org.omg.CORBA.ORB;
import org.omg.CORBA.ORBPackage.InvalidName;
import org.omg.PortableServer.POA;
import org.omg.PortableServer.POAHelper;
import org.omg.PortableServer.POAManagerPackage.AdapterInactive;
import org.omg.PortableServer.POAPackage.ServantNotActive;
import org.omg.PortableServer.POAPackage.WrongPolicy;

public class Server {

	public static void main(String[] args) throws InvalidName, AdapterInactive, ServantNotActive, WrongPolicy, IOException {
		ORB orb = ORB.init(args, null); /** Initialisation de l'ORB. */
		
		
		/** Récupération RootPOA, conversions et activation, doit être fait dans tous les cas **/
		org.omg.CORBA.Object rootobj = orb.resolve_initial_references("RootPOA"); 
		POA poa = POAHelper.narrow(rootobj);
		poa.the_POAManager().activate();
		/*ComptePOA servant = new CompteImplInherit(); création de l’objet serveur */ 
		
		serv_calcPOA servant = new serv_calcPOATie(new calcImpl());
		
		
		org.omg.CORBA.Object obj = poa.servant_to_reference(servant); /** enregistrement **/ 
		saveIOR("compte.ior", orb, obj); /** sauvegarde l’ior de obj dans compte.ior **/
		orb.run(); /** traitement des requêtes de clients **/ 
	}
	
	static void saveIOR(String fileName, ORB orb, org.omg.CORBA.Object obj) throws IOException {
		String ior = orb.object_to_string(obj); // représentation sous forme de string de l’ior 
		FileWriter fw = new FileWriter(fileName); // un flux de sortie vers un fichier 
		fw.write(ior); // rempli avec l’ior
		fw.close(); // et fermé
	}	
}
