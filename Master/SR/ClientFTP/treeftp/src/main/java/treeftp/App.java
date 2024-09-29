package treeftp;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintStream;
import java.net.UnknownHostException;

import treeftp.server.Client;
import treeftp.server.ClientRequest;
import treeftp.server.Connection;
import treeftp.utils.Tree;
import treeftp.commands.Commands;
import treeftp.commands.Parameters;

/**
 * Classe principale du projet
 */
public class App {

    /**
     * Fonction de lancement de l'application
     * 
     * @param args Les arguments de l'application.
     * @throws UnknownHostException Si une erreur de connection à un hôte survient
     * @throws IOException          Si une erreur d'entrée ou de sortie survient
     * @throws InterruptedException Si une erreur d'interruption survient
     */
    public static void main(String[] args) throws UnknownHostException, IOException, InterruptedException {
        OutputStream output = new FileOutputStream("out.txt");
        PrintStream printOut = new PrintStream(output);
        System.setErr(printOut);
        appMain(args);
    }

    /**
     * Fonction principale de l'application
     * 
     * @param args Les arguments de l'application.
     * @return True si l'application s'est bien exécutée, false sinon
     * @throws UnknownHostException Si une erreur de connection à un hôte survient
     * @throws IOException          Si une erreur d'entrée ou de sortie survient
     * @throws InterruptedException Si une erreur d'interruption survient
     */
    public static Boolean appMain(String[] args) throws UnknownHostException, IOException, InterruptedException {
        Commands request;
        ClientRequest requestHandlerCmd;
        Parameters parameters;
        Client client_cmd;

        // Creer la commande et vérifie si elle est valide
        // Dans le cas ou elle est invalide, il y a un message d'erreur
        request = new Commands();

        if (!request.checkParametersCommand(args)) {
            return false;
        }

        // Creer la connection et l'authentification au protocole FTP avec un client
        // en mode commande
        System.err.println("[-----------------------------------------");
        parameters = request.getParameters();
        client_cmd = new Client(parameters.getUrl(), 21,
                parameters.getUsername(), parameters.getPassword());
        requestHandlerCmd = client_cmd.getConnection().getRequest();

        if (!Connection.checkConnection(client_cmd, parameters)) {
            return false;
        }

        // Execute la commande et applique les paramètres
        System.err.println("-----------------------------------------");
        System.out.println();
        if (parameters.getPath() != "/") {
            requestHandlerCmd.changeRepository(parameters.getPath());
        }

        // Lancement de la fonction de recherche
        Tree.start(parameters, client_cmd);

        // Deconnecte le client commande
        requestHandlerCmd.disconnect();
        requestHandlerCmd.readRequest();
        client_cmd.getConnection().disconnect();
        return true;
    }

}
