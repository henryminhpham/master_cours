package org.psia.osgi.event;

import org.psia.osgi.BundleContext;

public interface ServiceListener {

	void onResolve(BundleContext c);
	
	void onClose(BundleContext c);
	
}

