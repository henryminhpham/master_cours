package org.util;

import oracle.kv.KVStore;

public abstract class AbstractExercice implements Exercice {

  protected final KVStore store;
  private boolean populate = false;

  public AbstractExercice(KVStore store) {
    this(store, false);
  }

  public AbstractExercice(KVStore store, boolean populate) {
    this.store = store;
    this.populate = populate;
  }

  @Override
  public boolean isPopulate() {
    return populate;
  }

  @Override
  public void setPopulate(boolean populate) {
    this.populate = populate;
  }

  @Override
  public Exercice populate() {
    return this;
  }

  @Override
  public void close() {
    store.close();
  }
}
