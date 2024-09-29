/**
 * @file Client.java
 * @brief Contient la classe client qui va gérer les connexions des clients
 * @version 1.0
 * @author Alexis Bernard & Tom Taffin
 * */
package serverFtp.Servers;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

import serverFtp.Commands.Command;
import serverFtp.Commands.CommandInvoker;

/**
 * Classe client qui va gérer les connexions des clients
 */
public class Client extends Thread{
    private String name; // Nom de l'utilisateur
    private String password; // Mot de passe de l'utilisateur
    private String root_path; // Chemin racine
    private String path; // Chemin courant
    private String ip; // Adresse IP
    private InputStream in_stream; // Stream de lecture de la socket des données

	// Commandes
    private Server serv; // Le serveur auquel le client est rattaché
    private String port; // Port de la socket de commande
    private Socket socket_command; // Socket du socket de commande
    private Boolean connected; //  Connexion ou non du socket de commande
    private BufferedReader in; // Buffer de lecture du socket de commande
    private PrintWriter out; // Buffer d'écriture du socket de commande

	// Data
	private String port_data; // Port de la socket des données
	private Socket socket_data; // Socket de la socket des données
    private BufferedReader in_data; // Buffer de lecture de la socket des données
    private PrintWriter out_data; // Buffer d'écriture de la socket des données
	private String old_path; // Ancien chemin

    /**
     * Constructeur de la classe client
     * @param socket_command Socket de commande
	 * @param address Adresse IP
	 * @param root_path Chemin racine
     * @throws IOException Exception IO
     */
    public Client(Socket socket_command, String address, String root_path, Server serv) throws IOException {
        this.name = null;
        this.password = null;
        this.root_path = root_path;
        this.path = "/";
        this.ip = address;
        this.port = String.valueOf(socket_command.getLocalPort());
        this.in_stream = null;
        this.serv = serv;
        this.socket_command = socket_command;
		this.socket_data = null;
		this.port_data = null;
        this.connected = true;
		this.in_stream = null;
        this.in = new BufferedReader( new InputStreamReader( socket_command.getInputStream()));
        this.out = new PrintWriter(socket_command.getOutputStream(),true);

    }

	/**
	 * Méthode run qui lance le thread
	 */
    public void run(){
        String line, commandLine, commandParam;
        Command commandSelect;
        String[] codeTab;        
        try{
            while((line = this.in.readLine()) != null && this.connected){
                System.out.println("Has read : " + line);
                codeTab = line.split(" ");
                commandLine = codeTab[0];
                commandParam = null;
                if(codeTab.length > 1){
                    commandParam = codeTab[1];
                }
                commandSelect = CommandInvoker.invoke(commandLine, this, commandParam);
                commandSelect.execute();
            }
        }catch(Exception e){
                System.err.println("ClientRunError: " + e);
        }
    }

    /**
     * Créer un client avec le socket de commande et initialise les buffers de lecture et d'écriture
     * @return true si le client a été créé, false sinon
     */
    public Boolean createClient(){
        try{
            this.in = new BufferedReader( new InputStreamReader( socket_command.getInputStream()));
            this.out = new PrintWriter(socket_command.getOutputStream());
            this.connected = true;
        }catch(Exception e){
            System.err.println("CreateClientError: " + e.getMessage());
            return false;
        }
        return true;
    };

    /**
     * Ferme le client
     * @return true si le client a été fermé, false sinon
     */
    public Boolean closeClient(){
        try{
            this.in.close();
            this.out.close();
            this.socket_command.close();
            this.connected = false;
        }catch(Exception e){
            System.err.println("CloseClientError: " + e.getMessage());
            return false;
        }
        return true;
    };

	/**
     * Créer un socket de données avec le port et l'adresse ip donnée en paramètre pour le client
     * @param port_data Port de la socket de données
     * @param hostname Adresse IP du serveur
     * @return true si le socket de données a été créé, false sinon
     */
    public Boolean createSocketData(String hostname, String port_data){
        try {
            this.socket_data = new Socket(hostname,Integer.valueOf(port_data));
            System.err.println(this.socket_data);
            this.port_data = port_data;
            this.in_data = new BufferedReader( new InputStreamReader( socket_data.getInputStream()));
            this.out_data = new PrintWriter(socket_data.getOutputStream());
            return true;
        } catch (Exception e) {
            System.err.println("CreateSocketDataError: " + e.getMessage());
            return false;
        }
    }
	
	/**
	 * Ferme le socket de données
	 * @return true si le socket de données a été fermé, false sinon
	 */ 
	public Boolean closeSocketData(){
		try{     
			this.in_data.close();
            this.out_data.close();
            this.socket_data.close();
        }catch(Exception e){
            System.err.println("CloseSocketDataError: " + e.getMessage());
            return false;
        }
        return true;	
	}

    /**
     * Retourne une chaine de caractère avec les informations du client
	 * @return String
     */
    public String toString(){
        return "Name: " + this.name + " Password: " + this.password + " Path: " + this.path + " Ip: " + this.ip + " Port: " + this.port;
    };

	/**
	 * Retourne le nom de l'utilisateur
	 * @return String
	 */
	public String getUsername() {
		return name;
	}

	/**
	 * Retourne le mot de passe de l'utilisateur
	 * @return String
	 */
    public String getPassword() {
        return password;
    }

	/**
	 * Retourne le chemin courant
	 * @return String
	 */
    public String getPath() {
        return path;
    }

	/**
	 * Retourne le chemin racine
	 * @return String
	 */
    public String getRootPath() {
        return root_path;
    }

	/**
	 * Retourne le chemin complet
	 * @return String
	 */
    public String getFullPath() {
        return root_path + path;
    }

	/**
	 * Met à jour le chemin courant
	 * @param path Le nouveau chemin à mettre à jour
	 */
	public void setPath(String path){
		this.path = path;
	}

	/**
	 * Retourne l'adresse IP
	 * @return String
	 */
    public String getIp() {
        return ip;
    }

	/**
	 * Retourne le port de la socket de commande
	 * @return String
	 */
    public String getPort() {
        return port;
    }

	/***
	 * Retourne le port de la socket de données
	 * @return String
	 */
	public String getPortData(){
		return port_data;
	}

	/**
	 * Retourne si le client est connecté ou non
	 * @return Boolean
	 */
    public Boolean isConnected() {
        return connected;
    }
	
	/**
	 * Retourne le buffer de lecture de la socket de commande
	 * @return PrintWriter
	 */
    public PrintWriter getOut() {
        return out;
    }

	/**
	 * Retourne le buffer d'écriture de la socket de commande
	 * @return BufferedReader
	 */
    public BufferedReader getIn() {
        return in;
    }

    public Socket getSocketCommand() {
        return socket_command;
    }

	/**
	 * Retourn la socket de données
	 * @return Socket
	 */
	public Socket getSocketData(){
		return socket_data;
	}

    public void setSocketData(Socket socket, String port) {
        this.port_data = port;
        this.socket_data = socket;
        try {
            this.in_data = new BufferedReader( new InputStreamReader( this.socket_data.getInputStream()));
            this.out_data = new PrintWriter(this.socket_data.getOutputStream(),true);
        } catch (IOException e) {
            System.err.println("Error : " + e.getMessage());
        }
    }

	/***
	 * Retourne le buffer de lecture de la socket de données
	 * @return BufferedReader
	 */
	public PrintWriter getOutData() {
        return out_data;
    }

	/**
	 * Retourne le buffer d'écriture de la socket de données
	 * @return BufferedReader
	 */
    public BufferedReader getInData() {
        return in_data;
    }

	/**
	 * Retourne le chemin ancien
	 * @return String
	 */
	public String getOldPath() {
		return old_path;
	}

	/**
	 * Met à jour le chemin ancien
	 * @param old_path Le nouveau chemin à mettre à jour
	 */
	public void setOldPath(String old_path) {
		this.old_path = old_path;
	}

    public Server getServ() {
        return this.serv;
    }

    public void setServ(Server serv) {
        this.serv = serv;
    }

	   /**
     * Retourne le stream de lecture de la socket de données
     * @return InputStream
     */
    public InputStream getInStream() {
        return in_stream;
    }    

    /**
     * Crée le stream de lecture de la socket de données
     * @param path Le chemin du fichier
     */
    public void createInpuStream(String path) {
        try {
            this.in_stream = new FileInputStream(path);
        } catch (IOException e) {
            System.err.println("CreateInputStreamError: " + e.getMessage());
        }
    }

    /**
     * Ferme le stream de lecture de la socket de données./c
     */
    public void closeInputStream() {
        try {
            this.in_stream.close();
        } catch (IOException e) {
            System.err.println("CloseInputStreamError: " + e.getMessage());
        }
    }
}
