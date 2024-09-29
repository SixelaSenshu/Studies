/**
 * @file DeleteCommand.java
 * @version 1.0
 * @authors Alexis Bernard et Tom Taffin
 */
package serverFtp.Commands;

 /**
  * Classe qui va gérer la commande de suppression de fichier
  */
public class DeleteCommand extends Command{
    

    @Override
	/**
	 * Méthode qui va exécuter la commande
	 */
    public void execute() {
		int resCode = CommandMaker.deleteContent(this.client, this.args[0]);
		CommandMaker.send(this.client.getOut(), resCode);
	}
}
