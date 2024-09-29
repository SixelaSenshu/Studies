package serverFtp.Commands;

public class SizeCommand extends Command{
	
	/**
	 * Constructeur de la classe SizeCommand
	 */
	public SizeCommand(){
		super();
	}

	@Override
	/**
	 * Méthode qui va exécuter la commande
	 */
	public void execute() {
		try {
			String size = CommandMaker.getSize(this.client, this.args[0]);
			CommandMaker.send(this.client.getOut(), 213,size);
		} catch (Exception e) {
			CommandMaker.send(this.client.getOut(), 451);
		}
	}
}
