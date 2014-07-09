package org.psia.osgi;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.net.URISyntaxException;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.Enumeration;
import java.util.jar.Attributes;
import java.util.jar.JarEntry;
import java.util.jar.JarFile;
import java.util.jar.Manifest;

public class BundleClassLoader extends URLClassLoader {

	private JarFile file;
	private Manifest mf;

	public BundleClassLoader(File file) throws IOException {
		super(new URL[] { file.toURI().toURL() });
		this.file = new JarFile(file);
		this.mf = this.file.getManifest();
	}

	public BundleClassLoader(URL url) throws IOException, URISyntaxException {
		this(new File(url.toURI()));
	}

	@Override
	public Class<?> findClass(String name) throws ClassNotFoundException {
		try {
			if (name.equals(".")) {
				Attributes attributes = mf.getMainAttributes();
				if (attributes == null) {
					throw new ClassNotFoundException(
							"Activator class property not found in the Manifest. You have to specify the Bundle-Activator property.");
				}
				name = attributes.getValue("Bundle-Activator");
				if (name == null) {
					throw new ClassNotFoundException(
							"Activator class property not found in the Manifest. You have to specify the Bundle-Activator property.");
				}
			}
			String path = name.replace('.', '/') + ".class";
			Enumeration<JarEntry> entries = file.entries();
			while (entries.hasMoreElements()) {
				JarEntry entry = entries.nextElement();
				if (entry.getName().equals(path)) {
					try (InputStream is = file.getInputStream(entry)) {
						byte[] content = new byte[is.available()];
						is.read(content);
						Class<?> resultClass = defineClass(name, content, 0,
								content.length);
						assert(resultClass != null);
						return resultClass;
					}
				}
			}
		} catch (IOException ex) {
			throw new ClassNotFoundException("An error occured", ex);
		}
		return null;
	}

	@Override
	public void close() throws IOException {
		file.close();
		super.close();
	}

}
