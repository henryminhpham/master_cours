package fr.upmc.srcs.tme3;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Annuaire extends Remote {
	
	public int addPersonne( Personne to_add ) throws RemoteException;
	public String getNumber ( String name ) throws RemoteException;

}