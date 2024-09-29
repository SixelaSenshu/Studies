
/**
 * Classe Client qui permet de créer un client pour une connection FTP à un hôte. Le client permet de créer une connexion
 * et de faire des requêtes au serveur FTP. Celui-ci peut être anonyme ou avoir des authentifiants.
 * @see ClientConnection pour voir l'implémentation de la connexion
 * @see ClientRequest pour voir l'implémentation des requêtes
 * @author Alexis Bernard
 * @version 1.0
 * @since 1.0
 */
package treeftp.server;

/**
 * Classe Client qui permet de mettre à jour les informations d'un client et de
 * créer une connection à un serveur FTP
 * avec une socket.
 * 
 * @see ClientConnection pour voir l'implémentation de la connexion
 */
public class Client {

    private String user; // Utilisateur
    private String password; // Mot de passe
    private String hostname; // Nom d'hôte
    private ClientConnection connection; // Connexion

    private int port;

    /**
     * Constructeur de la classe Client avec un utilisateur et un mot de passe
     * 
     * @param hostname Nom de l'hôte
     * @param port     Port de connexion
     * @param user     Utilisateur
     * @param password Mot de passe
     */
    public Client(String hostname, int port, String user, String password) {
        this.setHostname(hostname);
        this.setPort(port);
        this.setUser(user);
        this.setPassword(password);
        connection = new ClientConnection(this);
    }

    /**
     * Constructeur de la classe Client pour un client anonyme
     * 
     * @param hostname Nom de l'hôte
     * @param port     Port de connexion
     */
    public Client(String hostname, int port) {
        this.setHostname(hostname);
        this.setPort(port);
        this.setUser("null");
        this.setPassword("null");
        connection = new ClientConnection(this);
    }

    /**
     * Renvoie la connection du client
     * 
     * @return Sous forme de (ClientConnection)
     */
    public ClientConnection getConnection() {
        return connection;
    }

    /**
     * Renvoie le port utilisé actuel du client
     * 
     * @return Sous forme (int)
     */
    public int getPort() {
        return port;
    }

    /**
     * Renvoie le hostname utilisé actuel du client
     * 
     * @return Sous forme de (String)
     * 
     */
    public String getHostname() {
        return this.hostname;
    }

    /**
     * Renvoie l'utilisateur
     * 
     * @return Sous forme de (String)
     */
    public String getUser() {
        return user;
    }

    /**
     * Renvoie mot de passe
     * 
     * @return Sous forme de (String)
     */
    public String getPassword() {
        return password;
    }

    /**
     * Met à jour le port
     * 
     * @param port Le port à mettre à jour
     */
    public void setPort(int port) {
        this.port = port;
    }

    /**
     * Met à jour le nom d'hôte
     * 
     * @param hostname Nom d'hôte à mettre à jour
     */
    public void setHostname(String hostname) {
        this.hostname = hostname;
    }

    /**
     * Met à jour l'utilisateur
     * 
     * @param user Le nom d'utilisateur à mettre à jour
     */
    public void setUser(String user) {
        this.user = user;
    }

    /**
     * Met à jour le mot de passe
     * 
     * @param password Le mot de passe à mettre à jour
     */
    public void setPassword(String password) {
        this.password = password;
    }

}
