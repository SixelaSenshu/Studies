/**
 * @file WelcomeCommand.java
 * @version 1.0
 * @authors Alexis Bernard et Tom Taffin
 */
package serverFtp.Commands;

/**
 * Classe qui va gérer la commande de bienvenue
 * Celle-ci ce lance quand le client se connecte au serveur FTP
 */
public class WelcomeCommand extends Command{

	/**
	 * Constructeur de la classe WelcomeCommand
	 */
	public WelcomeCommand(){
		super();
	}
    @Override
	/**
	 * Méthode qui va exécuter la commande
	 */
    public void execute() {
        CommandMaker.send(this.client.getOut(), 220);
    }
    
}
