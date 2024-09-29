
/**
 * @file ChangeDirectoryCommand.java
 * @version 1.0
 * @authors Alexis Bernard et Tom Taffin
 */
package serverFtp.Commands;

 /**
  * Classe qui va gérer la commande CWD
  */
public class ChangeDirectoryCommand extends Command {
	/**
	 * Constructeur de la classe ChangeDirectoryCommand
	 */
	public ChangeDirectoryCommand(){
		super();
	}

	@Override
	/**
	 * Méthode qui va exécuter la commande
	 */
	public void execute() {
		int resCode = CommandMaker.changeDir(this.client, this.args[0]);
		CommandMaker.send(this.client.getOut(),resCode);
	}
}
