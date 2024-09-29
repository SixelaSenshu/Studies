
/**
* @file TypeCommand.java
* @version 1.0
* @authors Alexis Bernard & Tom Taffin
*/

package serverFtp.Commands;

/**
 * Classe qui va gérer la commande TYPE

 */
public class TypeCommand extends Command {
    
    @Override
	/**
	 * Méthode qui va exécuter la commande
	 */
    public void execute() {
        CommandMaker.send(this.client.getOut(), 200);
    }
}
