import java.io.PrintStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.Statement;

/**
 * NOM, Prenom 1 : BOURNAT Marjorie NOM, Prenom 2 : GALLARDO Kevin Binome :
 * Groupe :
 * 
 * La classe Generique
 **/

public class GeneriqueXHTML {

	/* les attributs */

	String server = "oracle.ufr-info-p6.jussieu.fr";
	String port = "1521";
	String database = "ora10";
	String user = "E1234567"; // votre login
	String password = "E1234567"; // le mot de passe (=login)

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

		/* initialisation */
		GeneriqueXHTML c = new GeneriqueXHTML();

		/* requete */
		c.traiteRequete(requete);
	}

	/**
	 * Constructeur : initialisation
	 **/
	private GeneriqueXHTML() {
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

			System.out
					.print("<?xml version=\"1.0\" encoding=\"ISO-8859-1\" ?>");
			System.out
					.print("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">");
			System.out.println("<html>");
			System.out.println("<head ><title>Résultat</title></head>");
			System.out.println("<body>");
			System.out
					.println("<h1>La requete est : </h1> select * from Joueur2");
			System.out.println("<h3>le resultat est : </h3>");
			System.out.println("<table border=\"2\">");

			String url = "jdbc:oracle:thin:@" + server + ":" + port + ":"
					+ database;

			connexion = DriverManager.getConnection(url, user, password);
	
			Statement lecture = connexion.createStatement();

			ResultSet resultat = lecture.executeQuery(requete);
			ResultSetMetaData info = resultat.getMetaData();

			System.out.print("<tr>");
			for (int i = 1; i <= info.getColumnCount(); i++) {
				String tuple = info.getColumnLabel(i);
				out.print("<th>" + tuple + "</th>");
			}
			System.out.println("</tr>");
			while (resultat.next()) {
				System.out.print("<tr>");
				for (int i = 1; i <= info.getColumnCount(); i++) {
					String tuple = resultat.getString(i);
					out.print("<td>" + tuple + "</td>");
				}
				System.out.println("</tr>");
			}
			System.out.println("</table>");
			System.out.println("</body>");
			System.out.println("</html>");

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
