package fr.upmc.srcs.tme3;

import java.rmi.RemoteException;
import java.util.HashMap;

public class AnnuaireImpl implements Annuaire{
	
	private HashMap<String,Personne> cache;
	
	public AnnuaireImpl( ) throws RemoteException{
		this.cache = new HashMap<String, Personne>();
	}
	
	public int addPersonne(Personne to_add){
		System.out.println("hello "+to_add.getName());
		this.cache.put(to_add.getName(), to_add);
		return this.cache.size();
	}

	public String getNumber(String name){
		Personne p;
		if(this.cache.containsKey(name)){
			p=this.cache.get(name);
			this.cache.remove(name);
			p.incCount();
			this.cache.put(name, p);
			return p.getNumber();
		}
		return "not found";
	}
	
}
