/**
 * @file UploadCommand.java
 * @version 1.0
 * @authors Alexis Bernard et Tom Taffins
 */
package serverFtp.Commands;
	
/**
 * Classe qui va gérer la commande Upload
 */
public class UploadCommand extends Command{

	/**
	 * Constructeur de la classe UploadCommand
	 */
    public UploadCommand(){
		super();
	}

    @Override
	/**
	 * Méthode qui va exécuter la commande
	 */
    public void execute() {
		try {
			this.client.createInpuStream(this.args[0]);
			CommandMaker.createFile(client, this.args[0]);
			int resCode = CommandMaker.uploadFile(this.client, this.args[0]);
			CommandMaker.send(this.client.getOut(), resCode);
		} catch (Exception e) {
			CommandMaker.send(this.client.getOut(), 451);
		}
	}
}