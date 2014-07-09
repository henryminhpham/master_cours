package org.exo3;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Personne extends Remote {

  String getPrenom() throws RemoteException;

  void setPrenom(String prenom) throws RemoteException;

  String getPhone() throws RemoteException;

  void setPhone(String phone) throws RemoteException;

  String getAdresse() throws RemoteException;

  void setAdresse(String adresse) throws RemoteException;

  int getRequested() throws RemoteException;

  void setRequested(int requested) throws RemoteException;

}
