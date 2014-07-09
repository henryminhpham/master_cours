package fr.upmc.srcs.tme3;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface PersonneParRefItf extends Remote{
	public String getName() throws RemoteException;
	public String getAdress() throws RemoteException;
	public String getNumber() throws RemoteException;
	public long getCount() throws RemoteException;
	public long incCount() throws RemoteException;
}
