package org.main;

import java.rmi.NotBoundException;
import java.rmi.RemoteException;

public class DirectoryClient {

  public static void main(String[] args) throws RemoteException, NotBoundException {
    org.exo1.DirectoryClient.main(args);
    org.exo2.DirectoryClient.main(args);
    org.exo3.DirectoryClient.main(args);
    org.exo4.DirectoryClient.main(new String[]{"127.0.0.1"});
    System.exit(0);
  }

}
