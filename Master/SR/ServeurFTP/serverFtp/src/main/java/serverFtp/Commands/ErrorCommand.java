/**
 * @file ErrorCommand.java
 * @version 1.0
 * @authors Alexis Bernard et Tom Taffin
 */
package serverFtp.Commands;

 /**
  * Classe qui va gérer les erreurs de commandes et les méthodes non implémentées
  */
public class ErrorCommand extends Command {

    @Override
	/**
	 * Méthode qui va exécuter la commande
	 */
    public void execute() {
        CommandMaker.send(this.client.getOut(), 502);
    }
    
}
