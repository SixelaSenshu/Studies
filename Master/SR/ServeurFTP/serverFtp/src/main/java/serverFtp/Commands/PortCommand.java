
/**
 * @file PortCommand.java
 * @version 1.0
 * @authors Alexis Bernard et Tom Taffin
 */

package serverFtp.Commands;

 /**
  * Classe qui va gérer la commande PORT
  
  */
public class PortCommand extends Command{
    
	/**
	 * Constructeur de la classe PortCommand
	 */
	public PortCommand(){
		super();
	}

    @Override
	/**
	 * Méthode qui va exécuter la commande
	 */
    public void execute() {
		String[] split = args[0].split(",");
		String ip_data = String.join(".", split[0], split[1], split[2], split[3]);
		int port_data = Integer.parseInt(args[0].split(",")[4]) * 256  + 
		Integer.parseInt(args[0].split(",")[5]);
		// ajout du port au serveur
		this.client.createSocketData(ip_data,String.valueOf(port_data));
        CommandMaker.send(this.client.getOut(), 200);
    }
}
