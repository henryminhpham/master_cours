package org.exo3;

import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

import org.main.DirectoryServer;

public class DirectoryClient {

  public static void main(String[] args) throws RemoteException, NotBoundException {
    Registry registry = LocateRegistry.getRegistry(DirectoryServer.PORT);
    Directory dir = (Directory) registry.lookup("exo3");
    Personne send = new PersonneImpl("olivier", "test", "0123456789");
    dir.put("pitton", send);
    dir.get("pitton");
    dir.get("pitton");
    Personne personne = dir.get("pitton"); 
    assert (send.equals(personne)) : "Les deux personnes ne sont pas identiques";
    if(false == send.equals(personne)) {
      throw new AssertionError("Les deux personnes ne sont pas identiques");
   } 
   System.out.println("Exercice 3 valide !");
  }

}
