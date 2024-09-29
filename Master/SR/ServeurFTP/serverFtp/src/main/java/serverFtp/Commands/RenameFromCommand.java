/**
 * @file RenameFromCommand.java
 * @version 1.0
 * @authors Alexis Bernard et Tom Taffin
 */
package serverFtp.Commands;
 /**
  * Classe qui va gérer la commande RenameFrom
  */
public class RenameFromCommand extends Command{

    @Override
	/**
	 * Méthode qui va exécuter la commande
	 */
    public void execute() {
		int resCode = CommandMaker.searchContent(this.client, this.args[0]);
        CommandMaker.send(this.client.getOut(), resCode);
    }
    
}
