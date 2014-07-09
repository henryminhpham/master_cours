package turtle.tools;

import java.io.File;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import org.eclipse.emf.cdo.CDOObject;
import org.eclipse.emf.common.util.URI;
import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.emf.ecore.resource.ResourceSet;
import org.eclipse.emf.ecore.resource.impl.ResourceSetImpl;
import org.eclipse.emf.ecore.xmi.XMIResource;
import org.eclipse.emf.ecore.xmi.impl.EcoreResourceFactoryImpl;
import org.eclipse.emf.ecore.xmi.impl.XMIResourceFactoryImpl;

import turtle.Choreography;
import turtle.Color;
import turtle.Farm;
import turtle.Forward;
import turtle.SetPen;
import turtle.Stage;
import turtle.Turtle;
import turtle.TurtleFactory;
import turtle.TurtlePackage;
import turtle.impl.TurtleFactoryImpl;

public class TurtleSerializer {

	@SuppressWarnings("unchecked")
	public <T extends CDOObject> T load(File file) {
		ResourceSet resourceSet = new ResourceSetImpl();
		Resource.Factory.Registry registry = resourceSet.getResourceFactoryRegistry();
		Map<String, Object> extensionToFactoryMap = registry.getExtensionToFactoryMap();
		extensionToFactoryMap.put("xmi", new XMIResourceFactoryImpl());
		resourceSet.getPackageRegistry().put(TurtlePackage.eNS_URI,
				TurtlePackage.eINSTANCE);
		URI uri = URI.createFileURI(file.getAbsolutePath());
		Resource resource = resourceSet.getResource(uri, true);
		if (resource.isLoaded() && resource.getContents().size() > 0) {
			return (T) resource.getContents().get(0);
		}
		return null;
	}

	public <T extends CDOObject> void save(T object, File file) {
		ResourceSet resourceSet = new ResourceSetImpl();
		Resource.Factory.Registry registry = resourceSet.getResourceFactoryRegistry();
		Map<String, Object> extensionToFactoryMap = registry.getExtensionToFactoryMap();
		extensionToFactoryMap.put("xmi", new XMIResourceFactoryImpl());
		extensionToFactoryMap.put("ecore", new EcoreResourceFactoryImpl());
		resourceSet.getPackageRegistry().put(TurtlePackage.eNS_URI,
				TurtlePackage.eINSTANCE);
		Resource packageResource = resourceSet.createResource(URI
				.createFileURI("Turtle.ecore"));
		packageResource.getContents().add(TurtlePackage.eINSTANCE);
		try {
			packageResource.load(null);
		} catch (IOException e1) {
			e1.printStackTrace();
			return;
		}
		URI uri = URI.createFileURI(file.getAbsolutePath());
		Resource resource = resourceSet.createResource(uri);
		resource.getContents().add(object);
		try {
			HashMap<String, Boolean> options = new HashMap<String, Boolean>();
			options.put(XMIResource.OPTION_SCHEMA_LOCATION, Boolean.TRUE);
			resource.save(options);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public static void main(String[] args) {
		TurtleSerializer serializer = new TurtleSerializer();
		// Chargement du stage
		Stage s = serializer.load(new File("example/Stage2.xmi"));
		System.out.println(s.display());
		// Chargement de la ferme
		Farm farm = serializer.load(new File("example/Farm2.xmi"));
		// Création du stage
		TurtleFactory factory = TurtleFactoryImpl.init();
		Stage stage = factory.createStage();
		// Paramétrage
		Color color = factory.createColor();
		color.setRed(255);
		stage.setBackgroundColor(color);
		Turtle turtle = factory.createTurtle();
		turtle.setName("turtle");
		// Ajout de la tortue dans la ferme
		farm.getContains().add(turtle);
		// On met le SetPen
		SetPen setPen = factory.createSetPen();
		setPen.setTarget(turtle);
		setPen.setUP(false);
		// On met la direction
		Forward forward = factory.createForward();
		forward.setTarget(turtle);
		forward.setLength(100);
		// On met le second SetPen
		SetPen setPen2 = factory.createSetPen();
		setPen2.setTarget(turtle);
		setPen2.setUP(true);
		// Création de la chorégraphie
		Choreography chore2 = factory.createChoreography();
		chore2.getSequence().add(forward);
		chore2.getSequence().add(setPen2);
		chore2.getSequence().add(setPen);
		// On ajoute la choré / ferme dans le stage 
		stage.getChoreographies().add(chore2);
		stage.getFarms().add(farm);
		// On sauvegarde la ferme
		File fileFarmJava = new File("example/Farm2-java.xmi");
		serializer.save(farm, fileFarmJava);
		// On recharge la ferme 
		serializer.load(fileFarmJava);
		// On sauvegarde le stage dans un fichier
		serializer.save(stage, new File("example/Stage2-java.xmi"));
	}
}
