import java.sql.*;
import java.io.*;


/**
 *  NOM, Prenom 1 :
 *  NOM, Prenom 2 :
 *  Binome        :
 *  Groupe        :
 *
 * La classe Sponsor
 **/
public class Sponsor {
    
    /* parametres de connexion */

    String url1 = "jdbc:oracle:thin:@oracle.ufr-info-p6.jussieu.fr:1521:ora10"; // base tennis
    String user1 = "E1234567";            // votre login
    String password1 = "E1234567";         // le mot de passe
    Connection connexionTennis = null;

    String url2 = "jdbc:oracle:thin:@oracle2.ufr-info-p6.jussieu.fr:1521:ora2"; // base des sponsors
    String user2 ="anonyme";             // acces anonyme
    String password2 ="anonyme";
    Connection connexionSponsor = null;

    PrintStream out = System.out;    // affichage des resulats a l'ecran
    
    /**
     * methode main: point d'entr�e
     **/
    public static void main(String a[]) {
        
        /* initialisation */
        Sponsor c = new Sponsor();
        
        /* test des m�thodes que vous avez �crites */
        c.traiteRequete();
    }
    
    /**
     * Constructeur : initialisation
     **/
    private Sponsor(){
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
     *  affiche le resultat d'une requete
     */
    public void traiteRequete() {
        try {
        	
			out.println("Connexion avec l'URL: " + url1);
			out.println("utilisateur: " + user1 + ", mot de passe: " + password1);
			connexionTennis = DriverManager.getConnection(url1, user1, password1);
			
			connexionSponsor = DriverManager.getConnection(url2, user2, password2);
			
			out.println("statement...");
			Statement lecture = connexionTennis.createStatement();
			Statement lecture2 = connexionSponsor.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_READ_ONLY);
			
			
			
			String requete = "select J.Nom, J.Nationalite, G.Sponsor from Joueur2 J, Gain2 G where J.NuJoueur = G.NuJoueur order by J.Nom";
			String requete2 = "select S.Nom, S.Nationalite from Sponsor S";
			
			connexionSponsor = DriverManager.getConnection(url2, user2, password2);
			
			out.println("execute la requete : " + requete);
			ResultSet resultat = lecture.executeQuery(requete);
			ResultSet resultat2 = lecture2.executeQuery(requete2);
			String result;
			boolean flag=true;
			while (resultat.next()) {
				String nom_j = resultat.getString(1);
				String nationalite = resultat.getString(2);
				String nom_sponsor = resultat.getString(3);
				resultat2.first();
				flag = true;
				while (flag){
					if (nom_sponsor.equals(resultat2.getString(1))){
						result = nom_j + ", " + nationalite + ", " + nom_sponsor + ", " + resultat2.getString(1);
					//	out.println(result);
					}
					flag = resultat2.next();
				}
			}

			
	    /* � compl�ter */


	}
	/* getion des exceptions */
	catch(Exception e){ gestionDesErreurs(e);}
    }
    
    //---------------------------------------------------------------------
    
    /* m�thodes pour la gestion des erreurs */
    
    protected void gestionDesErreurs(Exception e) {
	out.println("Probleme d'acces a la base: " + e);
	
	/* pour facilier le d�bogage,
	   afficher la ligne ou l'erreur s'est produite*/
	e.printStackTrace();
	
	/* En cas de pb d'acces, on ferme la connexion */
	try {
	    if (connexionTennis != null)
		connexionTennis.close();
	    if (connexionSponsor != null)
		connexionSponsor.close();
	}
	catch(Exception se) {
	    out.println("Tout autre probleme: " + se);
	}
        throw new RuntimeException("Arret immediat");
    }
    
}
