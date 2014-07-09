import java.sql.*;
import java.io.*;


/**
 *  NOM, Prenom 1 :BOURNAT, Marjorie
 *  NOM, Prenom 2 :GALLARDO, Kévin
 *
 * La classe Joueur
 **/
public class Joueur {
    
    /* Commentaire: initialisation des variables de la classe Joueur pour la connection */
    
    String server = "oracle.ufr-info-p6.jussieu.fr"; //url du serveur sgbd a connecter
    String port = "1521";
    String database = "ora10"; //
    String user = "1234567"; // identifiants user
    String password = "1234567";
    String requete = "select nom, prenom from Joueur2";

    Connection connexion = null;
    public static PrintStream out = System.out;    // affichage des r�sulats � l'ecran
    
    /**
     * methode main: point d'entr�e
     **/
    public static void main(String a[]) {

        /* Commentaire: création d'un Joueur afin de tester l'exécution d'une requête*/
        Joueur c = new Joueur();
        
	c.traiteRequete();
    }
    
    /**
     * Constructeur : initialisation
     **/
    protected Joueur(){
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
     *  Commentaire :
     *
     */
    public void traiteRequete() {
        try {

            /* Commentaire: concanénation des différents éléments qui constituent l'url nécessaire pour contacter le sgbd.
             * Puis appel a l'objet DriverManager afin de récupèrer la connexion  */
	    String url = "jdbc:oracle:thin:@" + server + ":" + port + ":" + database;
            connexion = DriverManager.getConnection(url, user, password);
            
            /* Commentaire: création d'un statement à partir de la connexion. */
            Statement lecture =  connexion.createStatement();
            
            /* Commentaire: exécution de la requête à partir du statement */
            ResultSet resultat = lecture.executeQuery(requete);
            
            /* Commentaire: lecture des tuples issus du résultat de la requête */
            while (resultat.next()) {
            
                String tuple = resultat.getString(1) + "\t" + resultat.getString(2);
                out.println(tuple);
            }

            /* Commentaire: fermeture des connections, statement... */
	    resultat.close();
	    lecture.close();
	    connexion.close();
        }

        /* Commentaire: récupération de l'exception en cas d'erreur durant le déroulement de la méthode traiteRequete */
        catch(Exception e){ Outil.gestionDesErreurs(connexion, e);}
    }
}
