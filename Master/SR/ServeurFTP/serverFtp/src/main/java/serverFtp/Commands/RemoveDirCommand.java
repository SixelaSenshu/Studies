/**
 * @file RemoveDirCommand.java
 * @version 1.0
 * @authors Alexis Bernard et Tom Taffin
 */
package serverFtp.Commands;

 /**
  * Classe qui va gérer la commande mkdir
  */
public class RemoveDirCommand extends Command {

	/**
	 * Constructeur de la classe RemoveDirCommand
	 
	 */
    public RemoveDirCommand(){
        super();
    }
    
	@Override
    /**
	 * Méthode qui va exécuter la commande
	 */
	public void execute() {
		int resCode = CommandMaker.removeDir(this.client, this.args[0]);
        CommandMaker.send(this.client.getOut(), resCode);
     }
    
}
