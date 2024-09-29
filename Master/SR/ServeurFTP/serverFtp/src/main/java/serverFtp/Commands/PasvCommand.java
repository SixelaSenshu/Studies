/**
 * @file PasvCommand.java
 * @version 1.0
 * @authors Alexis Bernard et Tom Taffin
 */
package serverFtp.Commands;

/**
 * Classe qui va gérer la commande PASV
 * */
public class PasvCommand extends Command  {

	/**
	 * Constructeur de la classe PasvCommand
	 */
    public PasvCommand(){
        super();
    }
	
    @Override
	/**
	 * Méthode qui va exécuter la commande
	 */
    public void execute() {
		String passiveMode = CommandMaker.passiveMode(this.client);
		CommandMaker.send(this.client.getOut(), 227, passiveMode);
    }
    
}
