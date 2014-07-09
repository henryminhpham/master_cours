import java.sql.*;
import java.io.*;

/**
 * NOM, Prenom 1 : BOURNAT Marjorie NOM, 
 * Prenom 2 : GALLARDO Kevin Binome :
 * Groupe :
 * 
 * La classe Generique
 **/
public class Generique2 {

	/* les attributs */

	String server = "oracle.ufr-info-p6.jussieu.fr";
	String port = "1521";
	String database = "ora10";
	String user = "anonyme"; // votre login
	String password = "anonyme"; // le mot de passe (=login)

	Connection connexion = null;
	static PrintStream out = System.out; // affichage des r�sulats � l'ecran

	/**
	 * methode main: point d'entr�e
	 **/
	public static void main(String param[]) {

		if (param.length == 0) {
			throw new RuntimeException("Pas de  requete, arret immediat");
		}

		/* requete */
		String requete = param[0];
		//out.println("La requete est " + requete);

		/* initialisation */
		Generique2 c = new Generique2();

		/* requete */
		c.traiteRequete(requete);
	}

	/**
	 * Constructeur : initialisation
	 **/
	private Generique2() {
		try {

			/* Chargement du pilote JDBC */
			/* driver Oracle */
			Class.forName("oracle.jdbc.driver.OracleDriver");
		} catch (Exception e) {
			Outil.erreurInit(e);
		}
	}

	/**
	 * La methode traiteRequete affiche le resultat d'une requete
	 */
	public void traiteRequete(String requete) {
		try {
			String url = "jdbc:oracle:thin:@oracle2.ufr-info-p6.jussieu.fr:1521:ora2";
			//out.println("Connexion avec l'URL: " + url);
			//out.println("utilisateur: " + user + ", mot de passe: " + password);
			connexion = DriverManager.getConnection(url, user, password);

			//out.println("statement...");
			Statement lecture = connexion.createStatement();

			//out.println("execute la requete : " + requete);
			ResultSet resultat = lecture.executeQuery(requete);
			ResultSetMetaData info = resultat.getMetaData();

			//out.println("resultat...");
			//for (int i = 1; i <= info.getColumnCount(); i++) {
				//String tuple = info.getColumnLabel(i) + " | ";
				//out.print(tuple);
			//}
			//System.out.print("\n");
			//System.out.println("----------------------------------------------------\n");
			while (resultat.next()) {
				//for (int i = 1; i <= info.getColumnCount(); i++) {
					String tuple = resultat.getString(1) + " | ";
					//out.print(tuple);
				//}
				//System.out.println("\n");
			}
			resultat.close();
			lecture.close();
			connexion.close();

		}

		/* getion des exceptions */
		catch (Exception e) {
			Outil.gestionDesErreurs(connexion, e);
		}
	}
}

