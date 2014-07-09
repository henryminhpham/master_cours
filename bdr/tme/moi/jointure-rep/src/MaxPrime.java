import java.sql.*;
import java.io.*;


/**
 *  NOM, Prenom 1 : BOURNAT Marjorie
 *  NOM, Prenom 2 : GALLARDO Kevin
 *  Binome        :
 *  Groupe        :
 *
 * La classe MaxPrime
 **/
public class MaxPrime {

    String server = "oracle.ufr-info-p6.jussieu.fr";
    String port = "1521";
    String database = "ora10";
    String user = "E1234567";            // votre login
    String password = "E1234567";         // le mot de passe
    Connection connexion = null;
    public static PrintStream out = System.out;    // affichage des r�sulats � l'ecran

    /**
     * methode main: point d'entr�e
     **/
    public static void main(String a[]) {
        MaxPrime c = new MaxPrime();
	c.traiteRequete();
    }
 
   
    /**
     * Constructeur : initialisation
     **/
    private MaxPrime(){
        try {

            /* Chargement du pilote JDBC */
	    Class.forName("oracle.jdbc.driver.OracleDriver");
        }
        catch(Exception e) {
            Outil.erreurInit(e);
        }
    }
    
    
    /**
     *  La methode traiteRequete
     *  
     */
    public void traiteRequete() {
        try {
	    String url = "jdbc:oracle:thin:@" + server + ":" + port + ":" + database;
	    out.println("Connexion avec l'URL: " + url);
	    out.println("utilisateur: " + user + ", mot de passe: " + password);
            connexion = DriverManager.getConnection(url, user, password);

	    /* Commentaire: La méthode statique de Outil permet d'écrire un message sur la sortie standard 
	     * et de récupérer la valeur entrée par l'utilisateur. Puis on concaténe les éléments afin d'avoir notre requête. */
	    String a1 = Outil.lireValeur("Saisir une annee");
	    String requete = "select nom, max(prime) from Gain2 g, Joueur2 j"
		+ " where g.nujoueur = j.nujoueur and annee = " + a1 + " group by nom";
            
	    /* Commentaire: création du Statement à partir de la connexion au sgbd
	     * exécution de la requête, puis affichage du résultat en itérant sur chacun des tuples du résultat */
	    out.println("statement...");
            Statement lecture =  connexion.createStatement();
            
	    out.println("execute la requete : " + requete);
            ResultSet resultat = lecture.executeQuery(requete);
            
	    out.println("resultat...");
            while (resultat.next()) {
                String tuple = resultat.getString(1) + "\t" + resultat.getString(2);
                out.println(tuple);
            }
	    resultat.close();
	    lecture.close();
	    connexion.close();
        }

        /* getion des exceptions */
        catch(Exception e){ Outil.gestionDesErreurs(connexion, e);}
    }
}
