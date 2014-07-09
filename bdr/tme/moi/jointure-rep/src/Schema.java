import java.io.PrintStream;
import java.sql.Connection;
import java.sql.DatabaseMetaData;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;

public class Schema {

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
		String table = param[0];
		out.println("" + table);

		/* initialisation */
		Schema c = new Schema();

		/* requete */
		c.InfoTable(table);
	}

	/**
	 * Constructeur : initialisation
	 **/
	private Schema() {
		try {

			/* Chargement du pilote JDBC */
			/* driver Oracle */
			Class.forName("oracle.jdbc.driver.OracleDriver");
		} catch (Exception e) {
			Outil.erreurInit(e);
		}
	}

	public void InfoTable(String table) {
		try {
			String url = "jdbc:oracle:thin:@" + server + ":" + port + ":"
					+ database;
			out.println("Connexion avec l'URL: " + url);
			out.println("utilisateur: " + user + ", mot de passe: " + password);

			connexion = DriverManager.getConnection(url, user, password);

			
			DatabaseMetaData infos = connexion.getMetaData();
			
			
			ResultSet resultat = infos.getColumns("", "%", table, "%"); 
			
			while (resultat.next()) {
				String attr = resultat.getString("COLUMN_NAME") + " | ";
				String type = resultat.getString("TYPE_NAME") + " | ";
				out.print(attr + type);
				System.out.println("\n");
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
