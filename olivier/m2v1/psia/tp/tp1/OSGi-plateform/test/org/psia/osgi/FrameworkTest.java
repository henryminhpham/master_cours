package org.psia.osgi;

import static org.junit.Assert.*;

import java.io.IOException;

import org.junit.Test;

public class FrameworkTest {

	private final String url = "bundle_test.jar";

	@Test
	public void testInstall() throws IOException {
		Framework f = new Framework();
		Bundle bundle = f.install(url);
		bundle.resolve();
		BundleContext context = bundle.getContext();
		assertEquals(context.getId(), 1);
		assertEquals(context.getFramework(), f);
		assertEquals(context.getUrl(), url);
		assertEquals(f.get(1), bundle);
		f.close();
	}

}
