
import java.rmi.Remote;
import java.rmi.AlreadyBoundException;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.rmi.server.UnicastRemoteObject;
import java.rmi.server.RemoteServer;
import java.rmi.server.ObjID;
import java.rmi.server.ServerRef;
import java.rmi.server.RemoteRef;

import java.util.HashMap;
import java.util.Set;

import java.net.URLClassLoader;
import java.net.URL;

import sun.rmi.server.UnicastServerRef;
import sun.rmi.transport.LiveRef;

public class Mdocregistry extends RemoteServer implements Registry {
	private HashMap<String, Remote> hm = new HashMap<String, Remote>();

	public Mdocregistry(int port) throws RemoteException {
		UnicastServerRef uref = new UnicastServerRef(new LiveRef(new ObjID(ObjID.REGISTRY_ID), port));
		ref = uref;
		uref.exportObject(this, null, true);
	}

	public void log(String msg) {
		System.out.println("[Mdoc Registry]: " + msg);
	}

	synchronized public void bind(String name, Remote obj) throws AlreadyBoundException {
		log("bind '" + name + "' to: " + obj);
		//		if(hm.get(name) != null)
			hm.put(name, obj);
			//		else
			//			throw new AlreadyBoundException(name);
	}

	synchronized public String[] list() {
		log("list");
		Set<String> s = hm.keySet();
		String res[] = new String[s.size()];
		s.toArray(res);
		return res;
	}

	synchronized public Remote lookup(String name) throws NotBoundException {
		log("lookup '" + name + "'");
		Remote res = hm.get(name);
		if(res != null)
			return res;
		else
			throw new NotBoundException(name);
	}
  
	synchronized public void rebind(String name, Remote obj) {
		log("rebind '" + name + "' to: " + obj);
		hm.put(name, obj);
	}

	synchronized public void unbind(String name) throws NotBoundException {
		log("unbind '" + name + "'");
		if(hm.remove(name) == null)
			throw new NotBoundException(name);
	}

	public static void main(String args[]) throws Exception {
		int port = 1099;
		
		if(args.length > 0 && args[0] != null)
			port = Integer.parseInt(args[0]);

		URL[] urls = sun.misc.URLClassPath.pathToURLs(".");
		ClassLoader cl = new URLClassLoader(urls);
		sun.rmi.server.LoaderHandler.registerCodebaseLoader(cl);

		//System.out.println("---> " + LocateRegistry.createRegistry(6789));
		Registry reg = new Mdocregistry(port);

		System.out.println("---> " + reg);
		System.out.println("Registry is up and running...");


		//		Registry r = LocateRegistry.getRegistry();
		//		r.rebind("coucou", r);

		while (true) {
			try {
				Thread.sleep(Long.MAX_VALUE);
			} catch (InterruptedException e) {
			}
		}
	}
}