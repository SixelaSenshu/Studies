package serverFtp.Commands;
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import serverFtp.Files.FileManager;
import serverFtp.Servers.Client;
import serverFtp.Servers.DataServer;

/**
  *@file CommandMaker.java
 * @version 1.0
 * @authors Alexis Bernard et Tom Taffin
 */

/**
 * Classe qui va gérer l'ensemble des codes retours et des messages du serveur.
 * Celui va donc également avoir la responsabilité de gérer les envoyer de messages au client.
 */
public class CommandMaker {
    
    private static final Map<Integer, String> codeMap = CommandMaker.initMap(); // Map des codes

	/**
	 * Constructeur de la classe CommandMaker
	 */
    private CommandMaker() {}

	/**
	 * Méthode qui va envoyer un message au client
	 * @param printer Le PrintWriter du client
	 * @param code Le code de la réponse
	 * @param args Les arguments
	 */
    static public void send(PrintWriter printer, int code, String... args) {
        String line = CommandMaker.messageFromCode(code);
		String toReplace;
		int i = 0;
		for (String arg : args) {
			i++;
			toReplace = "$" + String.valueOf(i);
			line = line.replace(toReplace, arg);
		}
        printer.println(line);
        printer.flush();
    }

	/**
	 * Méthode qui va envoyer des données au client
	 * @param printer Le PrintWriter du client
	 * @param args Les données
	 */
	static public void sendData(PrintWriter printer, List<String> args) {
		for (String line : args) {
			printer.println(line);
        	printer.flush();
		}
	}

	/**
	 * Méthode qui va retourner le message associé à un code
	 * @param code Le code
	 * @return Le message
	 */
    static private String messageFromCode(int code) {
        return CommandMaker.codeMap.get(code);
    }

	/**
	 * Méthode qui va lancer la recherche de données dans un dossier
	 * @param path Le chemin du dossier
	 * @return La liste des données
	 */
	static public List<String> retrieveDataFrom(String path) {
		return FileManager.getLines(path);
	}

	/**
	 * Méthode qui va changer le dossier courant du client
	 * @param client Le client
	 * @param move Le déplacement
	 * @return
	 */
	static public int changeDir(Client client, String move) {
		String newPath = FileManager.moveIfPossible(client.getPath(),client.getRootPath(), move);
		if (newPath == null) return 550;
		if (newPath == "") newPath = "/";
		client.setPath(newPath);
		return 250;
	}

	/**
	 * Méthode qui va créer un dossier
	 * @param client Le client
	 * @param dir Le dossier à créer
	 * @return Le code de retour
	 */
	static public int createDir(Client client, String dir) {
		Boolean res = FileManager.createDirIfPossible(client.getPath(), dir, client.getRootPath());
		if (res == false) return 550;
		return 256;
	}

	/**
	 * Méthode qui va effacer un dossier
	 * @param client Le client
	 * @param dir Le dossier à créer
	 * @return Le code de retour
	 */
	static public int removeDir(Client client, String dir) {
		int res = FileManager.removeDirIfPossible(client.getPath(), dir, client.getRootPath());
		if (res == 0) return 250;
		else if(res == 1)return 255;
		return 550;
	}

	/**
	 * Méthode qui va rechercher un contenu
	 * @param client Le client
	 * @param file Le fichier
	 * @return Le code de retour
	 */
	static public int searchContent(Client client, String file) {
		String res = FileManager.searchFileIfPossible(client.getPath(), file, client.getRootPath());
		if (res != null){
			client.setOldPath(res);
			return 200;
		}
		return 501;
	}

	/**
	 * Méthode qui va renvoyer le code de retour pour le mode passif
	 * @param client Le client
	 * @return Le code de retour
	 */
	static public String passiveMode(Client client) {
		Long port = client.getServ().getNextPort();
		client.getServ().getPortManager().addPort(port);
		String ip = client.getSocketCommand().getInetAddress().getHostAddress();
		Long diviseur = 256L;
		Long quotient = port / diviseur;
		Long reste = port % diviseur;
		new DataServer(client, ip, port.toString()).start();
		return String.format("(%s,%d,%d)",
				ip.replace(".", ","),
				quotient, reste);
	}

	/**
	 * Méthode qui va renommer un dossier
	 * @param client Le client
	 * @param oldName L'ancien nom
	 * @param newName Le nouveau nom
	 * @return
	 */
	static public int renameContent(Client client, String oldName, String newName) {
		int res = FileManager.renameContentIfPossible(client.getPath(), oldName, newName, client.getRootPath());
		if (res == 0) return 253;
		else if (res == 1) return 550;
		return 501;
	}

	/**
	 * Méthode qui va effacer un contenu
	 * @param client Le client
	 * @return Le code de retour
	 */
	static public int deleteContent(Client client, String file) {
		Boolean res = FileManager.deleteContentIfPossible(client.getPath(), client.getRootPath(),file);
		if (res == true) return 254;
		return 501;
	}

	/**
	 * Méthode qui va créer un fichier
	 * @param client Le client
	 * @param file Le fichier
	 * @return Le code de retour
	 */
	static public int createFile(Client client, String file) {
		Boolean res = FileManager.createFileIfPossible(client.getPath(), file, client.getRootPath());
		if (res == true) return 256;
		return 501;
	}

	/**
	 * Méthode qui va uploader un fichier
	 * @param client Le client
	 * @param file Le fichier
	 * @return Le code de retour
	 */
	static public int uploadFile(Client client, String file) {
		try{
			String path = FileManager.searchFileIfPossible(client.getPath(), file, client.getRootPath());
			FileOutputStream fileOutputStream = new FileOutputStream(path);
			BufferedOutputStream bufferedOutputStream = new BufferedOutputStream(fileOutputStream);
			BufferedReader inputStream = client.getInData();
			int bytesRead = 0;
			while ((bytesRead = inputStream.read()) != -1) {
				bufferedOutputStream.write(bytesRead);
			}
			bufferedOutputStream.close();
			fileOutputStream.close();
			inputStream.close();
			return 250;
		} catch (Exception e) {
			return 451;
		}
	}

	/**
	 * Méthode qui va télécharger un fichier pour le client
	 * @param client Le client
	 * @param file Le fichier
	 * @return Le code de retour
	 */
	static public int downloadFile(Client client, String file){
		try {
			String path = FileManager.searchFileIfPossible(client.getPath(), file, client.getRootPath());
			FileInputStream fileInputStream = new FileInputStream(path);
			BufferedInputStream bufferedInputStream = new BufferedInputStream(fileInputStream);
			PrintWriter outputStream = client.getOutData();
			int bytesRead = 0;
			while ((bytesRead = bufferedInputStream.read()) != -1) {
				outputStream.write(bytesRead);
			}
			bufferedInputStream.close();
			fileInputStream.close();
			outputStream.close();
			return 250;
		} catch (IOException e) {
			return 451;
		}
	}

	/**
	 * Méthode qui va retourner la taille d'un fichier
	 * @param client Le client
	 * @param file Le fichier
	 * @return
	 */
	public static String getSize(Client client, String file) {
		// return FileManager.getSizeIfPossible(client.getPath(), file, client.getRootPath());
		return "";
	}

	/**
	 * Méthode qui va créer l'ensemble des codes et des messages
	 * @return La map des codes
	 */
    static private Map<Integer, String> initMap() {
        Map<Integer, String> res = new HashMap<>();
		res.put(150, "150 File status okay; about to open data connection");
		res.put(200, "200 Command okay");
		res.put(211, "211 System status, or system help reply");
		res.put(213, "213 $1");
		res.put(215, "215 Ubuntu system type");
		res.put(220, "220 Service Let me cook ready for new user ");
		res.put(221, "221 Connection closed");
		res.put(226, "226 Closing data connection");
		res.put(227, "227 Entering Passive Mode $1");
		res.put(230, "230 User logged in, proceed");
		res.put(250, "250 Requested file action okay, completed");
		res.put(253, "257 Renamed content successfuly");
		res.put(254, "257 Deleted content successfuly");
		res.put(255, "550 The directory is not empty");
		res.put(256, "257 Content created");
        res.put(257, "257 \"$1\" is current directory");
		res.put(331, "331 User name okay, need password");
		res.put(451, "451 Requested action aborted: local error in processing");
		res.put(501, "501 Syntax error in parameters or arguments");
		res.put(502, "502 Command not implemented");
		res.put(550, "550 Unreachable path");
        return res;
    }
}
