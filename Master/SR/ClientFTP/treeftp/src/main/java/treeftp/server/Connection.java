package treeftp.server;

import java.io.IOException;
import java.net.UnknownHostException;

import treeftp.commands.Parameters;

public class Connection {

    private Connection() {
    }

    /**
     * Permet de lancer la connection et l'authentification au protocole FTP
     * avec un client et les paramètres de la commande
     * 
     * @param client Le client
     * @param param  Les paramètres de la commande
     * @return True si la connection et l'authentification ont réussi, false sinon
     * @throws UnknownHostException Si une erreur de connection à un hôte survient
     * @throws IOException          Si une erreur d'entrée ou de sortie survient
     */
    public static Boolean checkConnection(Client client, Parameters param)
            throws UnknownHostException, IOException {
        ClientConnection connection;
        Boolean isConnectedClient;
        System.err.println(
                "[Connection] Connection in progress to the server " + param.getUrl() + " on the port "
                        + client.getPort()
                        + "...");
        connection = client.getConnection();
        isConnectedClient = connection.connect();
        if (isConnectedClient) {
            System.err.println("[Connection] Connexion client has succeded !");
            Boolean isLogged = connection.getRequest().authentification();
            if (isLogged) {
                System.err.println("[Connection] Authentification has succed !");
            } else {
                System.err.println("(Connection]  Authentification has failed !");
                return false;
            }

        } else {
            System.err.println("[Connection] Connexion has failed !");
            return false;
        }
        return true;
    }

      /**
     * Permet de lancer la connection et l'authentification au protocole FTP
     * avec un client et les paramètres de la commande
     * 
     * @param client Le client
     * @param param  Les paramètres de la commande
     * @return True si la connection et l'authentification ont réussi, false sinon
     * @throws UnknownHostException Si une erreur de connection à un hôte survient
     * @throws IOException          Si une erreur d'entrée ou de sortie survient
     */
    public static Boolean checkReachableConnection(Client client,Parameters param) throws UnknownHostException, IOException{
        ClientConnection connection;
        Boolean isConnectedClient;
        System.err.println(
                "[Connection] Connection in progress to the server " + param.getUrl() + " on the port "
                        + client.getPort()
                        + "...");
        connection = client.getConnection();
        isConnectedClient = connection.connect();
        if (isConnectedClient) {
            System.err.println("[Connection] Connexion client has succeded !");

        } else {
            System.err.println("[Connection] Connexion has failed !");
            return false;
        }
        return true;

    }

}
