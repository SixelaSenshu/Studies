/**
 * @brief Contient la classe serveur qui va gérer les connexions des clients
 * @file Server.java
 * @version 1.0
 * @author Alexis Bernard & Tom Taffin
 */
package serverFtp.Servers;

import java.io.IOException;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

import serverFtp.Commands.Command;
import serverFtp.Commands.CommandInvoker;

/**
 * Classe serveur qui va gérer les connexions des clients
 */
public class Server extends Thread{
    private String ip; // Adresse IP
    private String port; // Port 
    private InetAddress address; // Adresse
    private ServerSocket serverSocket; // Socket du serveur
    private List<Client> clients; // Liste des clients
    private String root; // Chemin racine
	private PortManager portManager; // Gestionnaire de port
   
	/**
	* Constructeur de la classe client 
	* @param port Le port sur lequel le serveur va écouter
	* @param ip L'adresse ip du serveur
	* @throws IOException Exception IO
    */
    public Server(String port, String ip) throws IOException {
        this.ip = ip;
        this.port = port;
        this.serverSocket = null;
        this.clients = new ArrayList<Client>();
        this.address = InetAddress.getByName(this.ip);
        this.root = "./serverFtp/files";
		this.portManager = new PortManager(8000L, 65535L);
        this.portManager.addPort(Long.parseLong(port));
    }

	/**
	 * Méthode run qui va lancer le serveur
	 */
    public void run(){
		try{
			this.createServer();
			while(true){
				this.acceptClient(); 
			}
			// this.closeServer(); unreachable code
		}catch(IOException e){
			System.err.println("Error: " + e.getMessage());
		}
    }


    /**
     * Créer un serveur sur le port et l'adresse ip donnée en paramètre
     * @return Boolean
     * @throws NumberFormatException Exception si le port n'est pas un nombre
     * @throws IOException Exception si le port est déjà utilisé
     */
    public Boolean createServer() throws NumberFormatException, IOException{
        try{
            int port = Integer.parseInt(this.port);
            this.serverSocket = new ServerSocket(port, 0, this.address);
            this.serverSocket.setReuseAddress(true);
            this.serverSocket.setSoTimeout(60000);
            System.err.println("Server Socket : " + this.serverSocket);
            System.err.println(this.serverSocket.getInetAddress().getHostAddress());
            System.err.println(this.serverSocket.getLocalPort());
        }catch(NumberFormatException e){
            System.err.println("Error: port must be a number");
            return false;
        }catch(IOException e){
            System.err.println("Error: port already in use");
            return false;
        }
        return true;
    }

    /***
     * Fermé le serveur
     * @return Boolean
     * @throws IOException Exception si le serveur ne peut pas être fermé
     */
    public Boolean closeServer() throws IOException{
        try{
            this.serverSocket.close();
        }catch(IOException e){
            System.err.println("Error: " + e.getMessage());
            return false;
        }
        return true;
    }

	/**
	 * Accepte un client et le met dans la liste des clients.
	 * Celui-ci lance un message de bienvenue au client et démarre un thread pour le client
	 * 
	 * @return Boolean
	 * @throws IOException Exception si le client ne peut pas être accepté
	 */
    public Boolean acceptClient() throws IOException{
        try{
            Socket clientSocket = serverSocket.accept();
            Client client = new Client(clientSocket,this.ip, this.root, this);
            Command command = CommandInvoker.invoke("WELC", client);
			command.execute();
			this.clients.add(client);
			System.out.println("Received socket");
            client.start();
        }catch(IOException e){
            System.err.println("Error: " + e.getMessage());
            return false;
        }
        return true;
    }


	/**
	 * Méthode qui va retourner le prochain port disponible
	 * @return Le prochain de port
	 */
	public Long getNextPort(){
		return this.portManager.nextPort();
	}

	/**
	 * Méthode qui va retourner le gestionnaire de port
	 * @return Le gestionnaire de port
	 */
	public PortManager getPortManager(){
		return this.portManager;
	}
}
