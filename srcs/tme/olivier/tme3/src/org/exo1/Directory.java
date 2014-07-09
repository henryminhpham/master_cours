package org.exo1;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Directory extends Remote {

  String get(String name) throws RemoteException;
  
  void put(String name, String phone) throws RemoteException;
  
}
