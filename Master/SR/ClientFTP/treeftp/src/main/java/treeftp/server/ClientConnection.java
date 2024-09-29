
/**
 * Classe ClientConnection qui permet de manipuler la connection d'un client à un hôte. 
 * La classe permet de gérer les entrées et sorties de la connexion ainsi que la connexion elle même
 * au serveur.
 * 
 * @see Client pour voir l'implémentation du Client
 * @see ClientRequest pour voir l'implémentation des requêtes
 * @author Alexis Bernard
 * @version 1.0
 * @since 1.0
 */
package treeftp.server;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;

/**
 * Classe pour la connexion du client
 * Celui-ci contient les informations de la connexion et les flux d'entrée et de
 * sortie ainsi que les fonctions pour se connecter et se déconnecter du serveur
 */
public class ClientConnection {
    private Client client; // Le client
    private Socket socket; // Socket
    private BufferedReader buffer; // Buffer de lecture
    private InputStream in; // Flux d'entrée
    private InputStreamReader inReader; // Buffer de lecture
    private OutputStream out; // Flux de sortie
    private PrintWriter print; // Buffer d'écriture
    private ClientRequest request; // Requête
    private String path; // Chemin actuel

    /**
     * Constructeur de la classe ClientConnection
     * 
     * @param client Le client
     */
    public ClientConnection(Client client) {
        this.path = "/";
        this.client = client;
        this.request = new ClientRequest(this);
    }

    /**
     * Constructeur de la classe ClientConnection
     * 
     * @param path   Le chemin actuel
     * @param client Le client
     */
    public ClientConnection(Client client, String path) {
        this.path = path;
        this.client = client;
        this.request = new ClientRequest(this);
    }

    /**
     * Permet de se connecter au serveur
     * 
     * @return Si la connexion est réussite.
     * @throws UnknownHostException Si une erreur de connection à un hôte survient
     * @throws IOException          Si une erreur d'entrée ou de sortie survient
     */
    public Boolean connect() throws UnknownHostException, IOException {
        String messageRequest;
        socket = new Socket(client.getHostname(), client.getPort());
        if (this.isConnected()) {
            this.in = socket.getInputStream();
            this.out = socket.getOutputStream();
            this.inReader = new java.io.InputStreamReader(this.in);
            this.buffer = new BufferedReader(this.inReader);
            this.print = new PrintWriter(this.out, true);
            if (client.getPort() < 1024) {
                messageRequest = this.buffer.readLine();
                System.err.println("[Connection] Server > " + messageRequest);
                if (messageRequest.contains("220")) {
                    return true;
                } else {
                    System.out.println("The server is not available !");
                    return false;
                }
            }
            return true;
        } else

        {
            return false;
        }
    }

    /**
     * Permet de se déconnecter du serveur
     * 
     * @throws IOException Si une erreur d'entrée ou de sortie survient
     */
    public void disconnect() throws IOException {
        if (this.isConnected()) {
            socket.close();
        }
    }

    /**
     * Permet de savoir si le client est connecté
     * 
     * @return true si le client est connecté, false sinon
     */
    public Boolean isConnected() {
        if (socket.isConnected()) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * Renvoie la socket actuelle
     *
     * @return La socket
     */
    public Socket getSocket() {
        return this.socket;
    }

    /**
     * Renvoie le buffer de lecture
     * 
     * @return Le buffer de lecture
     */
    public BufferedReader getBufferedReader() {
        return this.buffer;
    }

    /**
     * Renvoie le buffer d'écriture
     * 
     * @return Le buffer d'écriture
     */
    public PrintWriter getPrintWriter() {
        return this.print;
    }

    /**
     * Renvoie le flux d'entrée
     * 
     * @return Le flux d'entrée
     */
    public InputStream getInputStream() {
        return in;
    }

    /**
     * Renvoie le buffer de lecture
     * 
     * @return Le buffer de lecture
     */
    public InputStreamReader getInputStreamReader() {
        return this.inReader;
    }

    /**
     * Renvoie le flux de sortie
     * 
     * @return Le flux de sortie
     */
    public OutputStream getOutputStream() {
        return out;
    }

    /**
     * Renvoie la requête
     * 
     * @return La requête
     */
    public ClientRequest getRequest() {
        return this.request;
    }

    /**
     * Renvoie le client
     * 
     * @return Le client
     */
    public Client getClient() {
        return client;
    }

    /**
     * Renvoie le chemin actuel
     * 
     * @return Le chemin actuel
     */
    public String getPath() {
        return path;
    }

    /**
     * Met à jour le chemin actuel
     * 
     * @param path Le chemin à mettre à jour
     */
    public void setPath(String path) {
        this.path = path;
    }
}
