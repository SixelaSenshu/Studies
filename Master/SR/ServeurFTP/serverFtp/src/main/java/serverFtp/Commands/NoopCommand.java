/**
 * Class NoopCommand
 * @package serverFtp\Commands
 * @version 1.0
 * @authors Alexis Bernard et Tom Taffin
 */

package serverFtp.Commands;

/**
 * Classe qui va gérer la commande NOOP
 */
public class NoopCommand extends Command{
	
	/*
	 * Constructeur de la classe NoopCommand
	 */
	public NoopCommand() {
		super();
	}

	/**
	 * Méthode qui va exécuter la commande
	 */
	public void execute() {
		CommandMaker.send(this.client.getOut(), 200);
	}
}
