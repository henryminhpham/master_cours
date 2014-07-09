/* @author jlejeune */

import java.io.IOException;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.BooleanWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.SequenceFile;
import org.apache.hadoop.io.SequenceFile.CompressionType;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.*;
import org.apache.hadoop.mapreduce.lib.input.*;
import org.apache.hadoop.mapreduce.lib.output.*;
import org.apache.hadoop.util.GenericOptionsParser;


public class MyPiEstimator {

	public static void main(String[] args) throws Exception {
		Configuration conf = new Configuration();
		conf.setBoolean("mapred.map.tasks.speculative.execution", false);
		conf.setBoolean("mapred.reduce.tasks.speculative.execution", false);

		String[] otherArgs = new GenericOptionsParser(conf, args).getRemainingArgs();
		if (otherArgs.length != 3) {
			System.err.println("Usage: Pi <nMaps> <nReduce> <nSample>");
			System.exit(2);
		}
		
		//parsage des parametres
		final int numMap = Integer.parseInt(otherArgs[0]);
		final int numReduce = Integer.parseInt(otherArgs[1]);
		final long numSamples = Long.parseLong(otherArgs[2]);

		//Configuration du Job
		Job job = new Job(conf, "Pi_calulator");
		job.setInputFormatClass(/*A DEFINIR*/);
		
		job.setMapOutputKeyClass(/*A DEFINIR*/);//type cle de sortie des maps
		job.setMapOutputValueClass(/*A DEFINIR*/);//type valeur de sortie des maps
		
		
		job.setOutputKeyClass(/*A DEFINIR*/);//type cle de sortie du MapReduce
		job.setOutputValueClass(/*A DEFINIR*/);//type valeur de sortie du MapReduce
		
		
		job.setOutputFormatClass(/*A DEFINIR*/);

		job.setMapperClass(/*A DEFINIR*/);
		// ATTENTION : Ne pas utiliser cette methode pour eviter les pb de compatibilite avec les types de cle/valeur
		//job.setCombinerClass(MyPiReducer.class); 
		job.setReducerClass(/*A DEFINIR*/);
		job.setNumReduceTasks(numReduce);
		job.setJarByClass(MyPiEstimator.class); 
				
		Path TMP_DIR = new Path("/TMP_PI");
		final Path inDir = new Path(TMP_DIR, "in");// chemin vers le repertoire d'entree
		final Path outDir = new Path(TMP_DIR, "out");// chemin vers le repertoire de sortie
		FileInputFormat.addInputPath(job,inDir);//déclaration du répertoire d'entrée
		FileOutputFormat.setOutputPath(job, outDir);//déclaration du répertoire de sortie
		// Recuperation d'une reference sur le systeme de fichier
		final FileSystem fs = FileSystem.get(conf);//récupération d'une référence sur le système de fichier
		if (fs.exists(TMP_DIR)) {
		 fs.delete(TMP_DIR, true);
		}
		if (!fs.mkdirs(inDir)) {
		 throw new IOException("Cannot create input directory " + inDir);
		}

		//*****************************************************************
		//*****  TODO : Definir les fichiers d'entree pour chaque map ****
		//*****************************************************************
		
		
		//aide: Si le input format est le SequenceFileInputFormat, 
		// Pour ecrire dans des fichiers avec le format SequenceFile utiliser l'objet SequenceFile.writer
		// pour initialiser cet objet ecrire le code
		// SequenceFile.Writer writer=
		//		Sequencefile.createWriter(fs,conf,<Path du fichier>,<classe de la cle>, <classe de la valeur>, CompressionType.NONE)
		// ecrire dans le fichier avec writer.append(<cle>,<valeur>)
		
		
		//soumission et lancement du job sur la plateforme
		job.waitForCompletion(true);

		//****************************************************************
		//*****  TODO : Recuperer et parser les fichiers de sorties ******
		//****************************************************************

		//****************************************************************************
		//*****           TODO : Calculer et Afficher la valeur de Pi           ******
		//****************************************************************************
	}	

}
