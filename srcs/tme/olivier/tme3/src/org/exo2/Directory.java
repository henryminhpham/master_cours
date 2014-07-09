package org.exo2;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Directory extends Remote {

  Personne get(String name) throws RemoteException;
  
  void put(String name, Personne phone) throws RemoteException;
  
}
