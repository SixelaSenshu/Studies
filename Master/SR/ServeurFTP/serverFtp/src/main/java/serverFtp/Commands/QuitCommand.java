/**
 * @file QuitCommand.java
 * @version 1.0
 * @authors Alexis Bernard et Tom Taffin
 */

package serverFtp.Commands;

 /**
  * Classe qui va gérer la commande QUIT
  */
public class QuitCommand extends Command {

	/**
	 * Constructeur de la classe QuitCommand
	 */
	public QuitCommand(){
		super();
	}	

	@Override
	/**
	 * Méthode qui va exécuter la commande
	 */
	public void execute() {
		CommandMaker.send(this.client.getOut(), 221);
		this.client.closeClient();
		// retirer le port de la liste des ports utilisés
	}
}
