package org.util;


import java.io.Closeable;

public interface Exercice extends Closeable {

  Exercice go() throws Exception;
  
  Exercice populate();
  
  boolean isPopulate();
  
  void setPopulate(boolean populate);
}
