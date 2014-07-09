package org.psia.osgi;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import java.io.File;
import java.io.IOException;

import org.junit.Test;

public class BundleClassloaderTest {

	@Test
	public void loadClassTest() throws ClassNotFoundException, IOException {
		BundleClassLoader bundleClassLoader = new BundleClassLoader(new File("bundle_test.jar"));
		@SuppressWarnings("unchecked")
		Class<Activator> activator = (Class<Activator>) bundleClassLoader.loadClass(".");
		assertTrue(activator != null);
		assertEquals(bundleClassLoader, activator.getClassLoader());
	}

}
