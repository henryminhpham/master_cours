package org.exo3;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class PersonneImpl extends UnicastRemoteObject implements Personne {

  private static final long serialVersionUID = 1L;

  private String prenom;
  private String adresse;
  private String phone;
  private int requested = 0;

  public PersonneImpl() throws RemoteException {
  }

  public PersonneImpl(String prenom, String adresse, String phone) throws RemoteException {
    this.prenom = prenom;
    this.adresse = adresse;
    this.phone = phone;
  }

  @Override
  public String getPrenom() {
    return this.prenom;
  }

  @Override
  public void setPrenom(String prenom) {
    this.prenom = prenom;
  }

  @Override
  public String getPhone() {
    return this.phone;
  }

  @Override
  public void setPhone(String phone) {
    this.phone = phone;
  }

  @Override
  public String getAdresse() {
    return this.adresse;
  }

  @Override
  public void setAdresse(String adresse) {
    this.adresse = adresse;
  }

  @Override
  public int getRequested() {
    return this.requested;
  }

  @Override
  public void setRequested(int requested) {
    this.requested = requested;
  }

  @Override
  public int hashCode() {
    final int prime = 31;
    int result = 1;
    result = prime * result + ((this.adresse == null) ? 0 : this.adresse.hashCode());
    result = prime * result + ((this.phone == null) ? 0 : this.phone.hashCode());
    result = prime * result + ((this.prenom == null) ? 0 : this.prenom.hashCode());
    result = prime * result + this.requested;
    return result;
  }

  @Override
  public boolean equals(Object obj) {
    if (this == obj)
      return true;
    if (obj == null)
      return false;
    if (obj instanceof Personne == false)
      return false;
    Personne other = (Personne) obj;
    try {
    if (this.adresse == null) {
      if (other.getAdresse() != null)
        return false;
    } else if (!this.adresse.equals(other.getAdresse()))
      return false;
    if (this.phone == null) {
      if (other.getPhone() != null)
        return false;
    } else if (!this.phone.equals(other.getPhone()))
      return false;
    if (this.prenom == null) {
      if (other.getPrenom() != null)
        return false;
    } else if (!this.prenom.equals(other.getPrenom()))
      return false;
    if (this.requested != other.getRequested())
      return false;
    return true;
    } catch(RemoteException e) {
      return false;
    }
  }

  @Override
  public String toString() {
    return prenom;
  }

}
