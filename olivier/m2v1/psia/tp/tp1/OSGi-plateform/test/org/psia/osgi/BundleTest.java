package org.psia.osgi;

import java.io.IOException;

import org.junit.Test;

public class BundleTest {

	@Test
	public void test() throws IOException {
		Framework f = new Framework();
		Bundle bundle = f.install("bundle_test.jar", true);
		bundle.resolve();
		bundle.start();
		bundle.update();
		bundle.stop();
		f.close();
	}
	
}
