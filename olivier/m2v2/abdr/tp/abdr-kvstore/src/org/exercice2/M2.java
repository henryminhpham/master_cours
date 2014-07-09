package org.exercice2;

import java.util.ArrayList;
import java.util.List;

import oracle.kv.KVStore;
import oracle.kv.Key;
import oracle.kv.Value;

import org.util.AbstractExercice;
import org.util.Exercice;

public class M2 extends AbstractExercice {

  private List<Key> keys;

  public M2(KVStore store) {
    super(store, false);
  }

  @Override
  public Exercice populate() {
    keys = new ArrayList<>(10);
    for (int i = 1; i <= 10; i++) {
      keys.add(Key.createKey("C1", "P" + i));
    }
    if (isPopulate()) {
      System.out.println("Réinitialisation des données...");
      Value value = Value.createValue("0".getBytes());
      for (int i = 0; i < 10; i++) {        
        store.put(keys.get(i), value);
      }
    }
    System.out.println("Avant les transactions");
    for (int i = 0; i < 5; i++) {
      System.out.println(new String(store.get(keys.get(i)).getValue().getValue()));
    }
    return super.populate();
  }

  @Override
  public Exercice go() throws Exception {
    System.out.println("Démarrage des transactions");
    for (int i = 0; i < 1000; i++) {
      new Transaction(store).commit(keys);
    }
    System.out.println("Fin des transactions");
    for (int i = 0; i < 5; i++) {
      System.out.println(new String(store.get(keys.get(i)).getValue().getValue()));
    }
    return this;
  }
}
