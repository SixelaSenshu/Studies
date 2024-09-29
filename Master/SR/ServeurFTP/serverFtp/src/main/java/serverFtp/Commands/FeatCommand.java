/**
 * @file FeatCommand.java
 * @version 1.0
 * @authors Alexis Bernard & Tom Taffin
 */

package serverFtp.Commands;

 /**
  * Classe qui va gérer la commande FEAT
  */
public class FeatCommand extends Command {

    @Override
	/**
	 * Méthode qui va exécuter la commande
	 */
    public void execute() {
        CommandMaker.send(this.client.getOut(), 211);
    }
    
}
