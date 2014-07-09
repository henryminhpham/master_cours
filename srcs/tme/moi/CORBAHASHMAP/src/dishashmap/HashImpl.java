package dishashmap;

import java.util.HashMap;

import dishashmap.hashmap_servPackage.AlreadyExists;


public class HashImpl implements hashmap_servOperations{

	private HashMap<String,Valeur> cache;
	
	@Override
	public boolean containsKey(String key) {
		// TODO Auto-generated method stub
		return cache.containsKey(key);
	}

	@Override
	public Valeur get(String key) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void set(String key, Valeur val) throws AlreadyExists {
		// TODO Auto-generated method stub
		cache.put(key, val);
		
	}

}
