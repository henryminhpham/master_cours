package fr.upmc.srcs.tme3;

import java.util.HashMap;

public class AnnuaireTestImpl implements Annuairetest {
	private HashMap<String, String> Annuaire;
	
	public AnnuaireTestImpl(){
		this.Annuaire = new HashMap<String,String>();	
	}
	
	public void addPerson(String nom, String tel){
		Annuaire.put(nom, tel);
	}
	
	public String getNumber(String nom){
		return Annuaire.get(nom);
	}
	
}
