package fr.upmc.srcs.tme3;

import java.io.Serializable;

public class Personne implements Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private String name;
	private String number;
	private String adress;
	private long count;
	public Personne( String pname, String pnumber, String padress){
		this.name = pname;
		this.number=pnumber;
		this.adress=padress;
		this.count=0;
	}
	public String getName(){
		return this.name;
	}
	public String getAdress() {
		return adress;
	}
	public String getNumber(){
		return this.number;
	}
	public long getCount(){
		return this.count;
	}
	public long incCount(){
		return this.count++;
	}
}
