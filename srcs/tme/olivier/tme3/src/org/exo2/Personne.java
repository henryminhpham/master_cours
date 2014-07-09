package org.exo2;

import java.io.Serializable;

public class Personne implements Serializable {

  private static final long serialVersionUID = 1L;

  private String prenom;
  private String adresse;
  private String phone;
  private int requested;

  public Personne() {
  }

  public Personne(String prenom, String adresse, String phone) {
    super();
    this.prenom = prenom;
    this.adresse = adresse;
    this.phone = phone;
  }

  public String getPrenom() {
    return this.prenom;
  }

  public void setPrenom(String prenom) {
    this.prenom = prenom;
  }

  public String getPhone() {
    return this.phone;
  }

  public void setPhone(String phone) {
    this.phone = phone;
  }

  public String getAdresse() {
    return this.adresse;
  }

  public void setAdresse(String adresse) {
    this.adresse = adresse;
  }

  public int getRequested() {
    return this.requested;
  }

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
    if (!(obj instanceof Personne))
      return false;
    Personne other = (Personne) obj;
    if (this.adresse == null) {
      if (other.adresse != null)
        return false;
    } else if (!this.adresse.equals(other.adresse))
      return false;
    if (this.phone == null) {
      if (other.phone != null)
        return false;
    } else if (!this.phone.equals(other.phone))
      return false;
    if (this.prenom == null) {
      if (other.prenom != null)
        return false;
    } else if (!this.prenom.equals(other.prenom))
      return false;
    if (this.requested != other.requested)
      return false;
    return true;
  }

  @Override
  public String toString() {
    return prenom;
  }

}
