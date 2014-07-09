package org.exercice1;


import oracle.kv.KVStore;
import oracle.kv.Key;
import oracle.kv.Value;

import org.util.AbstractExercice;
import org.util.Exercice;

public class A1 extends AbstractExercice{

   public A1(KVStore store) {
    super(store);
  }

  @Override
  public Exercice go() throws Exception {
    Key key = Key.createKey("P1");
    for(int i = 0 ; i < 1000 ; i++) {
      store.put(key, Value.createValue(Integer.toString(i + 1).getBytes()));
    }
    System.out.println(new String(store.get(key).getValue().getValue()));
    return this;
  }

}
