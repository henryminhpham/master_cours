package org.exercice1;

import java.util.UUID;

import oracle.kv.KVStore;
import oracle.kv.Key;
import oracle.kv.Value;
import oracle.kv.Version;

import org.util.AbstractExercice;
import org.util.Exercice;

public class A2 extends AbstractExercice {

  public A2(KVStore store) {
    super(store);
  }

  @Override
  public Exercice go() throws Exception {
    Key key = Key.createKey("P1");
    for (int i = 0; i < 1000; i++) {
      Value value = Value.createValue(Integer.toString(i + 1).getBytes());
      Version version = new Version(UUID.randomUUID(), i);
      store.putIfVersion(key, value, version);
    }
    System.out.println(new String(store.get(key).getValue().getValue()));
    return this;
  }

}