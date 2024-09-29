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
public class UpCommand extends Command{
    

    @Override
	/**
	 * Méthode qui va exécuter la commande
	 */
    public void execute() {
        int resCode = CommandMaker.changeDir(this.client, "..");
		CommandMaker.send(this.client.getOut(),resCode);
    }
}
