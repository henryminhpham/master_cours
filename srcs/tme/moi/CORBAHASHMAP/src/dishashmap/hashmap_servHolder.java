package dishashmap;

/**
* dishashmap/hashmap_servHolder.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from dishashmap.idl
* vendredi 4 avril 2014 12 h 40 CEST
*/

public final class hashmap_servHolder implements org.omg.CORBA.portable.Streamable
{
  public dishashmap.hashmap_serv value = null;

  public hashmap_servHolder ()
  {
  }

  public hashmap_servHolder (dishashmap.hashmap_serv initialValue)
  {
    value = initialValue;
  }

  public void _read (org.omg.CORBA.portable.InputStream i)
  {
    value = dishashmap.hashmap_servHelper.read (i);
  }

  public void _write (org.omg.CORBA.portable.OutputStream o)
  {
    dishashmap.hashmap_servHelper.write (o, value);
  }

  public org.omg.CORBA.TypeCode _type ()
  {
    return dishashmap.hashmap_servHelper.type ();
  }

}
