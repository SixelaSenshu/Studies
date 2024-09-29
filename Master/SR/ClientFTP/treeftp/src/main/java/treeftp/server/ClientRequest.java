/**
 * Classe ClientRequest qui permet de lancé des requêtes FTP avec un client et une connexion
 * Celui ci contient les fonctions pour écrire, envoyer et lire une requête FTP
 * Celui ci contient aussi les fonctions pour lancer les commandes FTP comme la lecture d'un dossier,
 * d'un répétoire, la modification du répétoire courant, le téléchargement d'un fichier, etc...
 * 
 * @see Client pour voir l'implémentation du Client
 * @see ClientConnection pour voir l'implémentation des connexions du client
 * @author Alexis Bernard
 * @version 1.0
 * @since 1.0
 */

package treeftp.server;

import java.io.BufferedReader;
import java.io.IOException;

/**
 * Classe pour les requêtes du client
 * Celle-ci contient les fonctions pour écrire, envoyer et lire une requête FTP
 * ainsi que les commandes standards pour les deux types de connexions (commande
 * et données)
 */
public class ClientRequest {
    private String request; // La requête du client
    private String messagelog; // Le message de log
    private ClientConnection connection; // La connexion du client
    private Client client; // Le client

    /**
     * Le constructeur de la classe ClientRequest
     * 
     * @param connection La connexion du client
     */
    public ClientRequest(ClientConnection connection) {
        this.connection = connection;
        this.client = connection.getClient();
        this.request = "";
        this.messagelog = "";
    }

    /**
     * Lis tous les données pour une requête de données envoyé.
     * @return L'ensemble des réponses du serveur sur le port des données
     * @throws IOException Si une erreur d'entrée ou de sortie survient
     * @throws InterruptedException Si une erreur d'interruption se produit
     */
    public String readAllRequest() throws IOException, InterruptedException {
        String line = "";
        String res = readRequest();
        line += res;
        Boolean isEnd = false;
        try {
            while ((res = readRequest()) != null) {
                if (res != null && res != "") {
                    line += "\n" + res;
                } else {
                    this.connection.getSocket().close();
                    isEnd = true;
                    System.err.println(this.readRequest());
                }
            }
        } catch (Exception e) {
            this.connection.getSocket().close(); // Si on ne capture plus de message, on ferme la socket pour ne pas arreter le programme
            System.err.println(e);
        }
        return line;

    }

    /**
     * Lis le retour du serveur après l'ecriture et l'envoie d'une requête avec les
     * fonctions writeRequest() et sendRequest()
     * 
     * @return Le retour du serveur sous forme de chaîne de caractère
     * @throws IOException Si une erreur d'entrée ou de sortie survient
     */
    public String readRequest() throws IOException {
        String line = "";
        BufferedReader buffer = connection.getBufferedReader();
        try {
            line = buffer.readLine();
            // System.err.println(line);
            if (line != null) {
                if (line.charAt(0) == '-' || line.charAt(0) == 'd') {
                    return line;
                }
                System.err.println(messagelog + line);
                return line;
            } else {
                System.err.println("null");
            }
            return null;
        } catch (Exception e) {
             // Si on ne capture pas de message, on ren pour ne pas arreter le programme
            return null;
        }
    }

    /**
     * Permet d'écrire une requête avec des arguments et une commande souhaitée
     * 
     * @param message La commande FTP à envoyer
     * @param args    Les arguments de la commande
     * @return true si la requête a été écrite, false sinon
     */
    public Boolean writeRequest(String message, String args[]) {
        if (message == null) {
            return false;
        }
        for (int i = 0; i < args.length; i++) {
            message += " " + args[i];
        }
        request = message;
        return true;
    }

    /**
     * Permet d'envoyer une requête au serveur
     */
    public void sendRequest() {
        System.err.println(messagelog + "Client>" + request);
        connection.getPrintWriter().println(request);
        connection.getPrintWriter().flush();
    }

    /**
     * Permet de lancer la commande d'autentification au protocole FTP avec un
     * client.
     * 
     * @return true si l'authentification a réussi, false sinon
     * @throws IOException Si une erreur d'entrée ou de sortie survient
     */
    public Boolean authentification() throws IOException {

        messagelog = "[Connection] ";
        System.err.println("[Connection] Authentification en cours...");
        String args[] = { client.getUser() };
        this.writeRequest("USER", args);
        this.sendRequest();
        this.readRequest();
        args[0] = client.getPassword();
        this.writeRequest("PASS", args);
        this.sendRequest();
        String request = this.readRequest();
        if (!request.contains("230")) {
            return false;
        } else {
            return true;
        }
    }

    /**
     * Permet de lancer la commande de déconnection au protocole FTP avec un client.
     * 
     * @throws IOException Si une erreur d'entrée ou de sortie survient
     */
    public void disconnect() throws IOException {
        messagelog = "[Connection] ";
        String args[] = {};
        this.writeRequest("QUIT", args);
        this.sendRequest();
        this.readRequest();
    }

    /**
     * Permet de lancer le mode passif du protocole FTP et de définir le port de
     * réception des données automatiquement
     * 
     * @return Le port de réception des données
     * @throws IOException Si une erreur d'entrée ou de sortie survient
     */
    public String PASV() throws IOException {
        messagelog = "[Setting] ";
        String args[] = {};
        this.writeRequest("PASV", args);
        this.sendRequest();
        String message = this.readRequest();
        System.err.println(message);
        if (message == null || !message.contains("227")) {
            return null;
        }
        int index = message.indexOf("(");
        message = message.substring(index + 1, message.length() - 1);
        long count = 0, res = 0;
        int index_six = 0;
        int index_five = 0;
        for (int i = 0; i < message.length(); i++) {
            if (message.charAt(i) != ',') {
                if (count == 5 && index_six == 0) {
                    index_six = i;
                } else if (count == 4 && index_five == 0) {
                    index_five = i;
                }
            } else {
                count++;
            }
        }
        String sub_string = message.substring(index_five, index_six);
        if (sub_string.contains(",")) {
            sub_string = sub_string.replace(",", "");
        }
        res = Integer.parseInt(sub_string) * 256;
        sub_string = message.substring(index_six, message.length());
        if (sub_string.contains(")")) {
            sub_string = sub_string.replace(")", "");
        }
        int get = Integer.parseInt(sub_string);
        return String.valueOf(res + get);
    }

    /**
     * Permet de récupérer le chemin courant du client sur le serveur
     * 
     * @return Le chemin courant du client sur le serveur
     * @throws IOException Si une erreur d'entrée ou de sortie survient
     */
    public String getCurrentPath() throws IOException {
        this.setMessageLog("[Command] ");
        String args[] = {};
        this.writeRequest("PWD", args);
        this.sendRequest();
        if (this.readRequest().contains("257")) {
            return this.readRequest();
        }
        return null;
    }

    /**
     * Permet de changer le chemin courant du client sur le serveur
     * 
     * @param path Le chemin courant du client sur le serveur
     * @return true si le chemin a été changé, false sinon
     * @throws IOException Si une erreur d'entrée ou de sortie survient
     */
    public Boolean changeRepository(String path) throws IOException {
        this.setMessageLog("[Command] ");
        String args[] = { path };
        this.writeRequest("CWD", args);
        this.sendRequest();
        String message = this.readRequest();
        if (message.contains("250")) {
            return true;
        }
        return false;
    }

    /**
     * Permet d'envoyer un message null pour maintenir la connnexion au serveur
     * 
     * @return Si le serveur répond ou non
     * @throws IOException Si une erreur d'entrée ou de sortie survient
     */
    public Boolean ping() throws IOException {
        this.setMessageLog("[Command] ");
        String args[] = {};
        this.writeRequest("NOOP", args);
        this.sendRequest();
        String message = this.readRequest();
        if (message.contains("200")) {
            return true;
        }
        return false;
    }

    /**
     * Permet de changer le chemin courant du client sur le serveur pour le parent
     * 
     * @return true si le chemin a été changé, false sinon
     * @throws IOException Si une erreur d'entrée ou de sortie survient
     */
    public Boolean changeParentRepository() throws IOException {
        this.setMessageLog("[Command] ");
        String args[] = {};
        this.writeRequest("CDUP", args);
        this.sendRequest();
        String message = this.readRequest();
        if (message.contains("250")) {
            return true;
        }
        return true;
    }

    /**
     * Permet de lister les fichiers et dossiers du chemin courant du client sur le
     * serveur. Après l'envoie de la requête, il faut lire le retour du serveur avec
     * la fonction readRequest() des que toutes les données sont lus
     * 
     * @param path le chemin ou il faut lister
     * @throws IOException Si une erreur d'entrée ou de sortie survient
     */
    public void showRepository(String path) throws IOException {
        this.setMessageLog("[Command] ");
        String args[] = { path };
        this.writeRequest("LIST", args);
        this.sendRequest();
    }

    /**
     * Permet de récupérer le message de log
     * 
     * @return Le message de log
     */
    public String getMessageLog() {
        return this.messagelog;
    }

    /**
     * Permet de récupérer la requête du client
     * 
     * @return La requête du client
     */
    public String getRequest() {
        return this.request;
    }

    /**
     * Permet de récupérer la connexion du client
     * 
     * @return La connexion du client
     */
    public ClientConnection getClientConnection() {
        return this.connection;
    }

    /**
     * Permet de récupérer le client
     * 
     * @return Le client
     */
    public Client getClient() {
        return this.client;
    }

    /**
     * Permet de changer le message de log
     * 
     * @param message Le message de log
     */
    public void setMessageLog(String message) {
        this.messagelog = message;
    }

}
