package org.exo1;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class DirectoryImpl extends UnicastRemoteObject implements Directory {

  private static final long serialVersionUID = 1L;
  final private Map<String, String> directory = new ConcurrentHashMap<>();
  
  public DirectoryImpl() throws RemoteException {
    super();
  }

  @Override
  public String get(String name) throws RemoteException {
    return directory.get(name);
  }

  @Override
  public void put(String name, String phone) throws RemoteException {
    directory.put(name, phone);
  }

}
