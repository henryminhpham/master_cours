package calculator;


/**
* calculator/serv_calcPOATie.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from calculator.idl
* vendredi 28 mars 2014 12 h 03 CET
*/

public class serv_calcPOATie extends serv_calcPOA
{

  // Constructors

  public serv_calcPOATie ( calculator.serv_calcOperations delegate ) {
      this._impl = delegate;
  }
  public serv_calcPOATie ( calculator.serv_calcOperations delegate , org.omg.PortableServer.POA poa ) {
      this._impl = delegate;
      this._poa      = poa;
  }
  public calculator.serv_calcOperations _delegate() {
      return this._impl;
  }
  public void _delegate (calculator.serv_calcOperations delegate ) {
      this._impl = delegate;
  }
  public org.omg.PortableServer.POA _default_POA() {
      if(_poa != null) {
          return _poa;
      }
      else {
          return super._default_POA();
      }
  }
  public int add (int val1, int val2)
  {
    return _impl.add(val1, val2);
  } // add

  public int sub (int val1, int val2)
  {
    return _impl.sub(val1, val2);
  } // sub

  public int mult (int val1, int val2)
  {
    return _impl.mult(val1, val2);
  } // mult

  public int div (int val1, int val2) throws calculator.serv_calcPackage.ZeroDiv
  {
    return _impl.div(val1, val2);
  } // div

  private calculator.serv_calcOperations _impl;
  private org.omg.PortableServer.POA _poa;

} // class serv_calcPOATie
