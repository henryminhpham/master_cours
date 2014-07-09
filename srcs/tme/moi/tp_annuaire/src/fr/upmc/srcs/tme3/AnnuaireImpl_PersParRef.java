package fr.upmc.srcs.tme3;

import java.rmi.RemoteException;
import java.util.HashMap;

public class AnnuaireImpl_PersParRef implements Annuaire_PersParRef{

	
	private HashMap<String,PersonneParRefItf> cache;
	
	public AnnuaireImpl_PersParRef( ) throws RemoteException{
		this.cache = new HashMap<String, PersonneParRefItf>();
	}
	
	public int addPersonne(PersonneParRefItf to_add) throws RemoteException{
		System.out.println("hello "+to_add.getName());
		this.cache.put(to_add.getName(), to_add);
		return this.cache.size();
	}

	public String getNumber(String name) throws RemoteException{
		PersonneParRefItf p;
		if(this.cache.containsKey(name)){
			p=this.cache.get(name);
			p.incCount();
			System.out.println("number of searches : "+p.getCount());
			return p.getNumber();
		}
		return "not found";
	}
	
}
