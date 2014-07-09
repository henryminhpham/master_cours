package fr.upmc.srcs.tme3;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Annuairetest extends Remote {
	public void addPerson (String nom, String tel) throws RemoteException;
	public String getNumber (String nom) throws RemoteException;
	
}
