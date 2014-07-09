package fr.upmc.srcs.tme3;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

public class Serveur {

	public static void main(String[] args) throws RemoteException {
		// TODO Auto-generated method stub
		AnnuaireTestImpl annuaire = new AnnuaireTestImpl();
		UnicastRemoteObject.exportObject(annuaire, 0);

		Registry registry = LocateRegistry.createRegistry(23456);
		registry.rebind("Annuaire", annuaire);

	}

}
