package fr.upmc.srcs.tme3;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;


public class Server {

	public static void main(String[] args) throws IOException {
		Annuaire myannuaire = new AnnuaireImpl();
		UnicastRemoteObject.exportObject(myannuaire, 0);

		Registry registry = LocateRegistry.createRegistry(23456);
		registry.rebind("Annuaire", myannuaire);
		//FileOutputStream fichier = new FileOutputStream("annuaire.ser");
		//ObjectOutputStream oos = new ObjectOutputStream(fichier);
		//oos.writeObject(myannuaire);
		//oos.flush();
		//oos.close();
	}
}