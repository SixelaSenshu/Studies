/**
 * Class AbortCommand
 * @package serverFtp\Commands
 * @version 1.0
 * @authors Alexis Bernard et Tom Taffin
 */
package serverFtp.Commands;

/**
 * Classe qui va gérer la commande ABOR
 */
public class AbortCommand extends Command{
	
	/**
	 * Constructeur de la classe AbortCommand
	 */
	public AbortCommand() {
		super();
	}

	/**
	 * Méthode qui va exécuter la commande
	*/
	public void execute() {
		CommandMaker.send(this.client.getOut(),225);
	}
}
