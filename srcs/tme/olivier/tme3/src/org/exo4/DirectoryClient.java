package org.exo4;

import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

import org.exo1.Directory;
import org.main.DirectoryServer;

public class DirectoryClient {

  public static void main(String[] args) throws RemoteException, NotBoundException {
    Registry registry = LocateRegistry.getRegistry(args[0], DirectoryServer.PORT);
    Directory dir = (Directory)registry.lookup("exo1");
    String phone = "0123456789";
    dir.put("pitton", phone);
    dir.put("voron", phone);
    String remotePhone = dir.get("pitton");
    assert(phone.equals(remotePhone)) : "Le numéro de téléphone est invalide !";
    if(false == phone.equals(remotePhone)) {
       throw new AssertionError("Le numéro de téléphone est invalide !");
    } 
    System.out.println("Exercice 4 valide !");
  }

}
