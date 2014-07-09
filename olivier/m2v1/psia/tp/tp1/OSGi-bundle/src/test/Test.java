package test;

import org.psia.osgi.Activator;
import org.psia.osgi.BundleContext;

public class Test implements Activator {

	@Override
	public void start(BundleContext f) {
		System.out.println("Je suis le bundle " + f.getId() + " et je démarre !");
		new SubTest();
	}

	@Override
	public void stop(BundleContext f) {
		System.out.println("Je suis le bundle " + f.getId() + " et je m'arrête !");
	}

}
