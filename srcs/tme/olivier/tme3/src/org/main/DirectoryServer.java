package org.main;

import java.rmi.AlreadyBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class DirectoryServer {
  
  static public final int PORT = 1099;

  public static void main(String[] args) throws RemoteException, AlreadyBoundException {
    Registry registry = LocateRegistry.createRegistry(PORT);
    System.err.println("Export de l'exercice 1...");
    registry.bind("exo1", new org.exo1.DirectoryImpl());
    System.err.println("Export de l'exercice 2...");
    registry.bind("exo2", new org.exo2.DirectoryImpl());
    System.err.println("Export de l'exercice 3...");
    registry.bind("exo3", new org.exo3.DirectoryImpl());
  }

}
