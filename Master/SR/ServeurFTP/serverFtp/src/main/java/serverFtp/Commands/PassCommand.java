
/**
 * @file PassCommand.java
 * @version 1.0
 * @authors Alexis Bernard et Tom Taffin
 * 
 */
package serverFtp.Commands;

 /**
  * Classe qui va gérer la commande PASS
  */
public class PassCommand extends Command{
    

    @Override
	/**
	 * Méthode qui va exécuter la commande
	 */
    public void execute() {
        CommandMaker.send(this.client.getOut(), 230);
    }
}
