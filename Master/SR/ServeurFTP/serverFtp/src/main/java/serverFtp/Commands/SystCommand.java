/**
 * @file SystCommand.java
 * @version 1.0
 * @authors Alexis Bernard & Tom Taffin
 */
package serverFtp.Commands;

 /**
  * Classe qui va gérer la commande SYST
  */
public class SystCommand extends Command{


    @Override
	/**
	 * Méthode qui va exécuter la commande
	 */
	public void execute() {
        CommandMaker.send(this.client.getOut(), 215);
    }
}
