/**
 * @file CommandInvoker.java
 * @version 1.0
 * @authors Alexis Bernard & Tom Taffin
 */
package serverFtp.Commands;

import java.util.HashMap;
import java.util.Map;

import serverFtp.Servers.Client;


 /**
  * La classe CommandInvoker va permettre d'invoquer une commande à partir d'une chaine de caractères qui représente la commande
  */
public class CommandInvoker {
    private static final Map<String, Command> map = CommandInvoker.initializeMap();

	/**
	 * Constructeur de la classe CommandInvoker
	 */
    private CommandInvoker(){}

	/**
	 * Méthode qui va invoquer une commande
	 * @param input La commande à invoquer
	 * @param client Le client qui a envoyé la commande
	 * @param args Les arguments de la commande
	 * @return La commande invoquée
	 */
	static public Command invoke(String input, Client client, String... args){
		Command requestCommand = map.get(input);
		if(requestCommand != null){
			requestCommand.setArgs(args);
            requestCommand.setClient(client);
		}else{
			System.err.println ("Warning :"+ input + "This command is not possible");
		}
		return requestCommand;
	}
	
	/**
	 * Méthode qui va initialiser la map des commandes
	 * @return La map des commandes
	 */
   	static private Map<String,Command> initializeMap() {
        Map<String, Command> res = new HashMap<>();
        res.put("WELC", new WelcomeCommand());
        res.put("TYPE", new TypeCommand());
        res.put("SYST", new SystCommand());
		res.put("PWD", new PathCommand());
		res.put("PORT", new PortCommand());
		res.put("PASV",new PasvCommand());
        res.put("PASS", new PassCommand());
        res.put("FEAT", new FeatCommand());
		res.put("USER",new ConnectCommand());
        res.put("AUTH", new ErrorCommand());
		res.put("LIST", new ListCommand());
		res.put("QUIT", new QuitCommand());
		res.put("CWD", new ChangeDirectoryCommand());
		res.put("CDUP", new UpCommand());
		res.put("MKD", new CreateDirCommand());
		res.put("RMD", new RemoveDirCommand());
		res.put("RNFR", new RenameFromCommand()); 
		res.put("RNTO", new RenameToCommand());
		res.put("DELE", new DeleteCommand());
		res.put("NOOP", new NoopCommand());
        res.put("ABOR", new AbortCommand());
        res.put("RETR", new RetrieveCommand());
		res.put("SIZE", new SizeCommand());
        res.put("STOR", new UploadCommand());

	    return res;
    }
}
