/**
 * @file ListCommand.java
 * @version 1.0
 * @authors Alexis Bernard et Tom Taffin
 */
package serverFtp.Commands;
import java.util.List;

 /**
  * Classe qui va gérer la commande LIST
  */
public class ListCommand extends Command {
	
	/**
	 * Constructeur de la classe ListCommand
	 
	 */
	public ListCommand(){
		super();
	}	

	@Override
	/**
	 * Méthode qui va exécuter la commande
	 */
	public void execute(){
		CommandMaker.send(this.client.getOut(), 150);
		List<String> res = CommandMaker.retrieveDataFrom(this.client.getFullPath());
		CommandMaker.sendData(this.client.getOutData(), res);
		this.client.closeSocketData();
		CommandMaker.send(this.client.getOut(), 226);
	}
}
