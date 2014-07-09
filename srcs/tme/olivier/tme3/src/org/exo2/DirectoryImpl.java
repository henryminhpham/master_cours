package org.exo2;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class DirectoryImpl extends UnicastRemoteObject implements Directory {

  private static final long serialVersionUID = 1L;
  final private Map<String, Personne> directory = new ConcurrentHashMap<>();
  
  public DirectoryImpl() throws RemoteException {
    super();
  }

  @Override
  public Personne get(String name) throws RemoteException {
    Personne personne = directory.get(name);
    if(personne != null) {
      personne.setRequested(personne.getRequested() + 1);
    }
    return personne;
  }

  @Override
  public void put(String name, Personne personne) throws RemoteException {
    directory.put(name, personne);
  }

}
