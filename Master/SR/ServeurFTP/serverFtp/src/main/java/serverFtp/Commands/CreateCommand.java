/**
 * @file CreateCommand.java
 * @version 1.0
 * @authors Alexis Bernard et Tom Taffin
 */
package serverFtp.Commands;


 /**
  * Classe qui va gérer la commande de création de fichiers
  */
public class CreateCommand extends Command{
	
	/**
	 * Constructeur de la classe CreateCommand
	 */
	public CreateCommand(){
		super();
	}

	@Override
	/**
	 * Méthode qui va exécuter la commande
	 */
	public void execute(){
		int resCode = CommandMaker.createFile(this.client, this.args[0]);
		CommandMaker.send(this.client.getOut(), resCode);
	}
} 
