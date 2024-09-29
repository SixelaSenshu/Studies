/**
* @file Command.java
* @version 1.0
* @authors Alexis Bernard et Tom Taffin
*/
package serverFtp.Commands;

import serverFtp.Servers.Client;
import serverFtp.Servers.Server;


 /**
  * Classe qui va gérer les commandes. Celle ci est abstraite et va permettre à toutes les commande d'hériter de cette classe.
 * Cette classe va permettre de gérer les commandes et d'appliquer le pattern Commande.
  */
public abstract class Command { 
    protected Server serv; // Le serveur
    protected String[] args; // Les arguments
    protected Client client; // Le client
    
	/**
	 * Constructeur de la classe Command
	 */
    public Command() {
        this.args = null;
    }

	/**
	 * Methode qui va ajouter les arguments
	 * @param args les arguments
	 */
    public void setArgs(String... args){
        this.args = args;
    }

	/**
	 * Methode qui va définir le client
	 * @param client le client
	 */
    public void setClient(Client client){
        this.client = client;
    }

	/**
	 * Méthode qui va définir le serveur
	 * @param serv le serveur
	 */
	public void setServer(Server serv){
		this.serv = serv;
	}

	/**
	 * Méthode qui va retourner le client
	 * @return le client
	 */
    public Client getClient(){
        return this.client;
    }

	/**
	 * Méthode qui va retourner les arguments
	 * @return les arguments
	 */
    public String[] args(){
        return this.args;
    }

	/**
	 * Méthode qui va retourner le serveur
	 */
	public Server getServer(){
		return this.serv;
	}

	/**
	 * Méthode qui va exécuter la commande
	 */
    abstract public void execute();
}
