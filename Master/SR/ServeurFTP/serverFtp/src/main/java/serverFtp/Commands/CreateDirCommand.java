/**
 * @file CreateDirCommand.java
 * @version 1.0
 * @authors Alexis Bernard et Tom Taffin
 */
package serverFtp.Commands;

 /**
  * Classe qui va gérer la commande mkdir
  */
public class CreateDirCommand extends Command {

	/**
	 * Constructeur de la classe CreateDirCommand
	 
	 */
    public CreateDirCommand(){
        super();
    }
    
	@Override
    /**
	 * Méthode qui va exécuter la commande
	 */
	public void execute() {
		int resCode = CommandMaker.createDir(this.client, this.args[0]);
        CommandMaker.send(this.client.getOut(), resCode);
     }
    
}
