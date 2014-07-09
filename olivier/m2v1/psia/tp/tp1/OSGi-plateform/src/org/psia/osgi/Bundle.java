package org.psia.osgi;

import java.io.Closeable;
import java.io.File;
import java.io.IOException;
import java.lang.management.ManagementFactory;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Classe principale représentant un Bundle OSGi. Cette classe a été améliorée pour permettre le déchargement de classe et donc
 * la désinstallation. Les méthodes antagonistes sont : resolve - close / start - stop. Le update provoque un déchargement de classe. 
 * @author pitton
 *
 */
public class Bundle implements Closeable {

	static private final Logger logger = Logger.getLogger(Bundle.class
			.getName());

	private BundleContext context;
	private Class<Activator> activatorClazz;
	private Activator activator;
	private BundleClassLoader loader;

	public Bundle(BundleContext context) {
		this.context = context;
		ManagementFactory.getClassLoadingMXBean().setVerbose(this.context.isVerbose());
	}

	public BundleContext getContext() {
		return context;
	}
	
	@SuppressWarnings("unchecked")
	public void resolve() {
		int state = context.getState();
		assert(state == BundleContext.UNINSTALLED);
		log(Level.INFO, "Démarrage de la résolution du bundle \"" + context.getId()
				+ "\"...");
		try {
			// On charge la class Activator depuis le JAR
			loader = new BundleClassLoader(new File(context.getUrl()));
			// La classe "." signifie que l'on doit aller chercher la classe spécifiée par Bundle-Activator
			// dans le manifest, toutes les autres classes sont chargées "naturellement" depuis le JAR.
			activatorClazz = (Class<Activator>) loader.loadClass(".");
			context.setState(BundleContext.RESOLVED);
			log(Level.INFO, "Bundle \"" + context.getId() + "\" résolu");
			// On notifie une installation
			context.fireResolve();
		} catch (Exception ex) {
			log(Level.SEVERE, "Erreur dans la résolution du bundle \"" + context.getId()
					+ "\"", ex);
		}
	}

	public void start() {
		context.setState(BundleContext.STARTING);
		try {
			log(Level.INFO, "Démarrage du bundle \"" + context.getId() + "\"");
			// On crée une instance de l'Activator que l'on démarre
			activator = activatorClazz.newInstance();
			activator.start(context);
			context.setState(BundleContext.STARTED);
		} catch (InstantiationException | IllegalAccessException ex) {
			log(Level.SEVERE, "Erreur dans le démarrage du bundle \"" + context.getId()
					+ "\"", ex);
		}
	}

	public void stop() {
		context.setState(BundleContext.STOPPING);
		log(Level.INFO, "Arrêt du bundle \"" + context.getId() + "\"");
		this.activator.stop(context);
		context.setState(BundleContext.RESOLVED);
	}

	public void update() {
		int oldState = context.getState();
		// Si le bundle était démarré, on le stoppe
		if (oldState == BundleContext.STARTED) {
			stop();
		}
		// On flush tout pour recharger les classes
		try {
			close();
		} catch (IOException ex) {
		}
		// On charge les classes
		resolve();
		// Si le bundle était démarré, on le démarre
		if (oldState == BundleContext.STARTED) {
			start();
		}
	}

	@Override
	public void close() throws IOException {
		int state = context.getState();
		// Si déjà désinstallé, on ne fait rien
		if(state == BundleContext.UNINSTALLED) {
			return;
		}
		// Si le bundle est démarré, on le stopee (STARTED -> STOPPING -> RESOLVED)
		if (state == BundleContext.STARTED) {
			stop();
		}
		// On enlève les références pouvant causer des problèmes pour le GC
		// Tout ce qui référence une classe du bundle doit être supprimé
		activator = null;
		activatorClazz = null;
		// On flush le classloader
		if (loader != null) {
			loader.close();
			loader = null;
		}
		// On lance le GC
		System.gc();
		context.setState(BundleContext.UNINSTALLED);
		log(Level.INFO, "Le bundle \"" + context.getId() + "\" a été désinstallé");
		// On notifie une fermeture
		context.fireClose();
	}

	private void log(Level level, String message) {
		log(level, message, null);
	}

	private void log(Level level, String message, Throwable ex) {
		if (context.isVerbose())
			logger.log(level, message, ex);
	}
}
