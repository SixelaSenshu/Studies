/**
 * @file RenameToCommand.java
 * @version 1.0
 * @authors Alexis Bernard et Tom Taffin
 */
package serverFtp.Commands;
 /**
  * Classe qui va gérer la commande RenameTo
  */
public class RenameToCommand extends Command{

    @Override
	/**
	 * Méthode qui va exécuter la commande
	 */
    public void execute() {
		int resCode = CommandMaker.renameContent(this.client,this.client.getOldPath(), this.args[0]);
		CommandMaker.send(this.client.getOut(), resCode);
    }
    
}
