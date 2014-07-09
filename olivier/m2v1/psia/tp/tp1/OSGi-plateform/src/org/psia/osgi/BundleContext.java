package org.psia.osgi;

import org.psia.osgi.event.ServiceListener;

/**
 * Le contexte d'un bundle. Contient toutes les informations utiles pouvant être
 * passées aux Activator
 * 
 * @author pitton
 * 
 */
public class BundleContext {

	static final int UNINSTALLED = 0;
	static final int INSTALLED = 1;
	static final int RESOLVED = 2;
	static final int STARTING = 3;
	static final int STARTED = 4;
	static final int STOPPING = 5;

	private String url;
	private int id;
	private Framework framework;
	private boolean verbose;
	private int state;

	public BundleContext(String url, int id, Framework framework,
			boolean verbose) {
		this.url = url;
		this.id = id;
		this.framework = framework;
		this.verbose = verbose;
		this.state = UNINSTALLED;
	}

	public int getState() {
		return state;
	}

	public void setState(int state) {
		this.state = state;
	}

	public String getUrl() {
		return url;
	}

	public int getId() {
		return id;
	}

	public Framework getFramework() {
		return framework;
	}

	public boolean isVerbose() {
		return verbose;
	}

	void fireResolve() {
		framework.fireResolve(this);
	}

	void fireClose() {
		framework.fireClose(this);
	}

	public void addServiceListener(ServiceListener listener) {
		framework.addServiceListener(listener);
	}

	public void removeServiceListener(ServiceListener listener) {
		framework.removeServiceListener(listener);
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + id;
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		BundleContext other = (BundleContext) obj;
		if (id != other.id)
			return false;
		return true;
	}

}
