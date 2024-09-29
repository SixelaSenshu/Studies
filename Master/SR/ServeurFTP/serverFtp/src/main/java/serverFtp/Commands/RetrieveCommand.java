/**
 * Class RetrieveCommand
 * @package serverFtp\Commands
 * @version 1.0
 * @authors Alexis Bernard et Tom Taffin 
 */

 package serverFtp.Commands;

 /**
  * Classe qui va gérer la commande RETR
  */
 public class RetrieveCommand extends Command{
	 
	 /*
	  * Constructeur de la classe RetrieveCommand
	  */
	 public RetrieveCommand() {
		 super();
	 }
 
	 /**
	  * Méthode qui va exécuter la commande
	  */
	 public void execute() {
		 int resCode = CommandMaker.downloadFile(this.client, this.args[0]);
		 CommandMaker.send(this.client.getOut(), resCode);
	 }
 }