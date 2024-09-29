/**
 * @file ConnectCommand.java
 * @version 1.0
 * @authors Alexis Bernard et Tom Taffin
 */
package serverFtp.Commands;

 /**
  * Classe qui va gérer la commande de connection
  */
public class ConnectCommand extends Command {

	/**
	 * Constructeur de la classe ConnectCommand
	 
	 */
    public ConnectCommand(){
        super();
    }
    
	@Override
    /**
	 * Méthode qui va exécuter la commande
	 */
	public void execute() {
        CommandMaker.send(this.client.getOut(), 331);
     }
    
}
