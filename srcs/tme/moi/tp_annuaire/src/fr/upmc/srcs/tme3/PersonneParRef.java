package fr.upmc.srcs.tme3;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class PersonneParRef extends UnicastRemoteObject implements PersonneParRefItf{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private String name;
	private String number;
	private String adress;
	private long count;

	public PersonneParRef(String pname, String pnumber, String padress) throws RemoteException{
		this.name = pname;
		this.number = pnumber;
		this.adress = padress;
		this.count = 0;
	}

	public String getName() {
		return this.name;
	}

	public String getAdress() {
		return adress;
	}

	public String getNumber() {
		return this.number;
	}

	public long getCount() {
		return this.count;
	}

	public long incCount() {
		return this.count++;
	}

}
