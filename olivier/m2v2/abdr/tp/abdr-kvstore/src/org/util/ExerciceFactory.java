package org.util;


import oracle.kv.KVStore;

import org.exercice1.A1;
import org.exercice1.A2;
import org.exercice2.M1;
import org.exercice2.M2;

public class ExerciceFactory {

  public ExerciceFactory() {
  }
  
  public Exercice createA1(KVStore store) {
    return new A1(store);
  }
  
  public Exercice createA2(KVStore store) {
    return new A2(store);
  }
  
  public Exercice createM1(KVStore store) {
    return new M1(store);
  }
  
  public Exercice createM2(KVStore store) {
    return new M2(store);
  }

}
