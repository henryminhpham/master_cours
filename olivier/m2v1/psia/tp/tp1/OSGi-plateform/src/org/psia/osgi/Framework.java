package org.psia.osgi;

import java.io.Closeable;
import java.io.IOException;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import org.psia.osgi.event.ServiceListener;

/**
 * Représentation de la plateforme OSGI
 * @author pitton
 *
 */
public class Framework implements Closeable {

	private int id = 0;
	final private Map<Integer, Bundle> bundles;
	final private Set<ServiceListener> listeners;

	public Framework() {
		bundles = new HashMap<>();
		listeners = new HashSet<>();
	}

	public Bundle install(String url, boolean verbose) {
		// Installation du bundle et enregistrement dans la plateforme.
		Bundle bundle = new Bundle(new BundleContext(url, ++id, this, verbose));
		bundles.put(id, bundle);
		return bundle;
	}

	public Bundle install(String url) {
		return install(url, false);
	}

	public Bundle get(int id) {
		return bundles.get(id);
	}

	/**
	 * Notifie tous les listener d'une installation. Méthode appelée uniquement par la classe Bundle
	 * @param context Le contexte du bundle installé
	 */
	void fireResolve(BundleContext context) {
		for (ServiceListener listener : listeners) {
			listener.onResolve(context);
		}
	}


	/**
	 * Notifie tous les listener d'une désinstallation. Méthode appelée uniquement par la classe Bundle
	 * @param context Le contexte du bundle désinstallé
	 */
	void fireClose(BundleContext context) {
		for (ServiceListener listener : listeners) {
			listener.onClose(context);
		}
	}

	/**
	 * Enregistrement d'un listener. Appelé par BundleContext
	 * @param listener
	 */
	void addServiceListener(ServiceListener listener) {
		listeners.add(listener);
	}

	/**
	 * Désenregistrement d'un listener. Appelé par BundleContext
	 * @param listener
	 */
	void removeServiceListener(ServiceListener listener) {
		listeners.remove(listener);
	}

	@Override
	public void close() throws IOException {
		for (Bundle bundle : bundles.values()) {
			bundle.close();
		}
		bundles.clear();
	}

}
