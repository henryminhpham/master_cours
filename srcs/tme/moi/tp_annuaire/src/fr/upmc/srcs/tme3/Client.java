package fr.upmc.srcs.tme3;

import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class Client {

	public static void main(String[] args) throws RemoteException, NotBoundException {
		PersonneParRefItf yo = new PersonneParRef("coicoin", "42", "rue de l'avenue");
		Registry r = LocateRegistry.getRegistry("localhost", 23456);
		
		Annuaire_PersParRef c_myannuaire = (Annuaire_PersParRef) r.lookup("Annuaire");
		c_myannuaire.addPersonne(yo);
		System.out.println("number of coicoin : "+c_myannuaire.getNumber("coicoin"));
		System.out.println("number of coicoin : "+c_myannuaire.getNumber("coicoin"));
	}
}