
/**
 * Ce fichier contient la classe Commands qui permet de vérifier les arguments de la commande treeFtp
 * et de mettre à jours les paramètres de la commande.
 * @see Parameters pour voir l'implémentation des paramètres
 * @author Alexis Bernard
 * @version 1.0
 * @since 1.0
 */

package treeftp.commands;

import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;

/**
 * Classe pour les commandes: La commande à une structure à suivre afin d'être
 * valide :
 * La commande se poursuit de la manière suivante :
 * treeftp [url] [user] [password] [options]
 * [url] = arg[0] : L'url de connection
 * Optionnel :
 * [user] = arg[1] : Nom d'utilisateur
 * [password] = arg[2] : Mot de passe
 * [options] = arg[...] : Les options
 * ou
 * treeftp [url] [options]
 * [url] = arg[0] : L'url de connection
 * Optionnel :
 * [options] = arg[...] : Les options
 * 
 * @see Parameters pour voir l'implémentation des paramètres
 */
public class Commands {
    private Parameters parameters; // Les paramètres de la commandes
    private String args[]; // Les arguments de la commandes
    private int pos; // La position de lecture des arguments
    private int sizeArgs; // La taille des arguments
    public Boolean haveLogin;// Si la connection est anonyme ou non

    /**
     * Constructeur pour les commandes treeftp
     */
    public Commands() {
        this.parameters = new Parameters();
        this.args = null;
        this.pos = 0;
        this.sizeArgs = 0;
        this.haveLogin = false;
    }

    /**
     * Verifie si la commande est correctement saisie et renvoie le message d'erreur
     * en conséquence
     * 
     * @param args Les arguments de la commande
     * @return Si la commande est valide ou non
     * @throws UnknownHostException Si une erreur de connection à un hôte survient
     * @throws IOException          Si une erreur d'entrée ou de sortie survient
     */
    public Boolean checkParametersCommand(String args[]) throws UnknownHostException, IOException {
        this.args = args;
        this.sizeArgs = args.length;
        if (this.args.length == 0) {
            System.out.println("Parameters undefined ! ");
            return false;
        }
        if (this.args[0].charAt(0) == '-' && this.args[0].charAt(1) == 'h') {
            helpCommand();
            return false;
        }
        System.err.println("[Checking] Checking of adress ...");
        if (!checkPath(this.args[0])) { // L'addresse
            return false;
        }
        if (this.args.length > 1) {
            this.pos = 1;
            System.err.println("[Checking] Checking of login parameters ...");
            if (this.args[pos].charAt(0) != '-') { /// MDP
                System.err.println("[Checking] Login : " + this.args[pos]);
                this.parameters.setUser(this.args[pos]);
                if (this.args.length < 3) {
                    System.out.println("Password undefined ! ");
                    return false;
                }
                if (this.args[pos + 1].charAt(0) == '-') {
                    System.out.println("Password undefined ! ");
                    return false;
                }

                haveLogin = true;
                System.err.println("[Checking] Password : " + this.args[pos + 1]);
                this.parameters.setPassword(this.args[pos + 1]);
                this.pos = 3;
            } else {
                this.pos = 1; // Paramètres optionnels
            }
            System.err.println("[Checking] Checking of optional parameters ...");
            for (int i = this.pos; i < this.sizeArgs; i++) {
                int res = checkTypeArgument();
                if (0 == res) {
                    System.out.println("Bad or missing argument");
                    return false;
                } else if (res == 2) {
                    i++;
                }
                this.pos++;
            }
        }
        return true;
    }

    /**
     * Verifie si l'argument saisie est valide et si il est correctement utilisé
     * 
     * @return Si l'argument est valide ou non
     */
    private int checkTypeArgument() {
        char firstLetterArg = this.args[this.pos].charAt(0);
        char secondLetterArg, thirdLetterArg;
        switch (firstLetterArg) {
            case '-':
                secondLetterArg = this.args[this.pos].charAt(1);
                switch (secondLetterArg) {
                    case 'l': // Profondeur
                        if (this.pos + 1 >= this.sizeArgs) {
                            System.out.println("[Checking] Deepness undefined ! ");
                            return 0;
                        }
                        String count = this.args[this.pos + 1];
                        this.pos++;
                        if (!checkDeep(Integer.parseInt(count))) {
                            return 0;
                        }
                        return 2;
                    case 'j': // Format
                        checkFormat("Json");
                        return 1;
                    case 'i': // Interruption
                        checkInterrupt();
                        return 1;
                    case 'e': // Exploration
                        thirdLetterArg = this.args[this.pos].charAt(2);
                        if (thirdLetterArg == 'l' || thirdLetterArg == 'd') {
                            checkExploration(thirdLetterArg);
                        } else {
                            System.out.println("[Checking] Bad exploration argument ! ");
                            return 0;
                        }
                        return 1;
                    case 'p': // Chemin
                        if (this.pos + 1 >= this.sizeArgs) {
                            System.out.println("[Checking] Path undefined ! ");
                            return 0;
                        }
                        String path = this.args[this.pos + 1];
                        checkPathToLocate(path);
                        this.pos++;
                        return 2;
                    case 's': // Recherche
                        if (this.pos + 1 >= this.sizeArgs) {
                            System.out.println("[Checking] File search undefined ! ");
                            return 0;
                        }
                        String pathToSearch = this.args[this.pos + 1];
                        System.out.println(pathToSearch);
                        checkFileToSearch(pathToSearch);
                        this.pos++;
                        return 2;
                    case 'd': // Droits
                        Boolean isWrong = false;
                        parameters.setDisplayFile(false);
                        parameters.setDisplayRight(false);
                        parameters.setDisplayFolder(false);
                        for (int i = 2; i < this.args[this.pos].length(); i++) {
                            thirdLetterArg = this.args[this.pos].charAt(i);
                            switch (thirdLetterArg) {
                                case 'f':
                                case 'r':
                                case 'd':
                                    checkDisplayMode(thirdLetterArg);
                                    break;
                                default:
                                    isWrong = true;
                                    break;
                            }
                        }
                        if (isWrong) {
                            System.out.println("[Checking] Bad right argument ! ");
                            return 0;
                        }
                        return 1;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
        return 3;
    }

    /**
     * Verifie le paramètre d'exploration de l'arbre et le met à jour en conséquence
     * 
     * @param type Le type d'exploration
     * @return Si l'argument est valide ou non
     */
    private void checkExploration(char type) {
        if (type == 'l') {
            System.err.println("[Checking] Light exploration");
            this.parameters.setDeeplyExplore();
        } else if (type == 'd') {
            System.err.println("[Checking] Deeply exploration");
            // this.parameters.setLightlyExplore();
        } else {
            System.err.println("[Checking] Deeply exploration");
        }
    }

    /**
     * Verifie le paramètre d'interruption de l'arbre et le met à jour en
     * conséquence
     * 
     * @return Si l'argument est valide ou non
     */
    private void checkInterrupt() {
        System.err.println("[Checking] Interrupt allowed");
        this.parameters.setAllowedInterrupt(true);
    }

    /**
     * Verifie le paramètre de profondeur et le met à jour en conséquence
     * 
     * @param count La profondeur voulu.
     * @return si l'argument est valide ou non
     */
    private Boolean checkDeep(int count) {
        if (count < 0) {
            return false;
        }
        System.err.println("[Checking] Deepness : " + count);
        this.parameters.setDeep(count);
        return true;
    }

    /**
     * Verifie l'url de connection et le met à jour. Si la connection échoue, alors
     * soit l'url nécessite d'autre paramètre, soit il n'existe pas
     * 
     * @param url L'url de connection
     * @return Si le chemin est valide ou non
     * @throws UnknownHostException Si une erreur de connection à un hôte survient
     * @throws IOException          Si une erreur d'entrée ou de sortie survient
     */
    private Boolean checkPath(String url) throws UnknownHostException, IOException {
        System.err.println("[Checking] Adress : " + url);
        Socket socket = new Socket(url, 21);
        if (socket.isConnected()) {
            System.err.println("[Checking] Reachable !");
            this.parameters.setUrl(url);
            socket.close();
            return true;
        } else {
            // Faire les différents cas
        }
        System.err.println("[Checking] Unreachable !");
        socket.close();
        return false;
    }

    /**
     * Verifie l'argument pour le format de retour de l'arbre et le met à jour en
     * conséquence
     * 
     * @param args Le type de format.
     */
    private void checkFormat(String arg) {
        if (arg == "Json") {
            System.err.println("[Checking] Defined format : Json");
            this.parameters.setIsJson();
        }
    }

    /**
     * Met à jour le paramètre de droits d'affichage
     * 
     * @param mode
     */
    private void checkDisplayMode(char mode) {
        switch (mode) {
            case 'f':
                this.parameters.setDisplayFile(true);
                break;
            case 'r':
                this.parameters.setDisplayRight(true);
                break;
            case 'd':
                this.parameters.setDisplayFolder(true);
                break;
            default:
                break;
        }
    }

    /**
     * Met à jour le chemin de recherche
     * 
     * @param path Le chemin de recherche
     */
    private void checkPathToLocate(String path) {
        this.parameters.setPath(path);
    }

    /**
     * Met à jour le fichier de recherche
     * 
     * @param path Le chemin de recherche
     */
    private void checkFileToSearch(String path) {
        this.parameters.setSearch(true, path);
    }

    /**
     * Renvoie les paramètres
     * 
     * @return Les paramètres
     */
    public Parameters getParameters() {
        return this.parameters;
    }

    /**
     * Permet d'afficher l'ensemble des commandes disponibles
     */
    public void helpCommand() {
        System.out.println("Usage: treeftp [url] [user] [password] [options]");
        System.out.println("       treeftp [url] [options]");
        System.out.println("       treeftp -help");
        System.out.println("Options:");
        System.out.println("  -l [deepness] : Set the deepness of the tree");
        System.out.println("  -j : Set the format of the tree to Json");
        System.out.println("  -i : Set the interruption of the tree");
        System.out.println("  -e [l/d] : Set the exploration of the tree");
        System.out.println("  -p [path] : Set the path to locate");
        System.out.println("  -s [file] : Set the file to search");
        System.out.println("  -d {f/r/d} : Set the rules display mode (many possible)");
        System.out.println("  -help : Display this help");
    }
}
