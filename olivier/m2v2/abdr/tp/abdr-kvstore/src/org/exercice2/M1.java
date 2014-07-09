package org.exercice2;

import java.util.ArrayList;
import java.util.List;

import oracle.kv.KVStore;
import oracle.kv.Key;
import oracle.kv.Value;

import org.util.AbstractExercice;
import org.util.Exercice;

public class M1 extends AbstractExercice {

  public M1(KVStore store) {
    super(store);
  }

  @Override
  public Exercice go() throws Exception {
    List<Key> keys = new ArrayList<>();
    for (int i = 1; i <= 10; i++) {
      keys.add(Key.createKey("C1P" + i));
    }
    for (int i = 0 ; i <= 1000; i++) {
      store.put(keys.get(0), Value.createValue(Integer.toString(i + 1).getBytes()));
      store.put(keys.get(1), Value.createValue(Integer.toString(i + 1).getBytes()));
      store.put(keys.get(2), Value.createValue(Integer.toString(i + 1).getBytes()));
      store.put(keys.get(3), Value.createValue(Integer.toString(i + 1).getBytes()));
      store.put(keys.get(4), Value.createValue(Integer.toString(i + 1).getBytes()));
    }
    for(int i = 0 ; i < 5 ; i++) {
      System.out.println(new String(store.get(keys.get(i)).getValue().getValue()));
    }
    return this;
  }

}
