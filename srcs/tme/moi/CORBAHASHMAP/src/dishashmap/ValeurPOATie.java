package dishashmap;


/**
* dishashmap/ValeurPOATie.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from dishashmap.idl
* vendredi 4 avril 2014 12 h 40 CEST
*/

public class ValeurPOATie extends ValeurPOA
{

  // Constructors

  public ValeurPOATie ( dishashmap.ValeurOperations delegate ) {
      this._impl = delegate;
  }
  public ValeurPOATie ( dishashmap.ValeurOperations delegate , org.omg.PortableServer.POA poa ) {
      this._impl = delegate;
      this._poa      = poa;
  }
  public dishashmap.ValeurOperations _delegate() {
      return this._impl;
  }
  public void _delegate (dishashmap.ValeurOperations delegate ) {
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
  public dishashmap.Valeur get ()
  {
    return _impl.get();
  } // get

  public void set (dishashmap.Valeur val)
  {
    _impl.set(val);
  } // set

  private dishashmap.ValeurOperations _impl;
  private org.omg.PortableServer.POA _poa;

} // class ValeurPOATie
