
/**
 * La classe pour les paramètres de la commande treeftp. Celle-ci contient les valeurs des arguments de la commande treeftp.
 * @see Commands pour voir l'implémentation des commandes
 * @author Alexis Bernard
 * @version 1.0
 * @since 1.0
 */
package treeftp.commands;

/**
 * La classe pour les paramètres de la commande treeftp. Celle-ci contient les
 * valeurs des arguments de la commande treeftp.
 * Les différentes options sont :
 * url : L'url de connection
 * user : Le nom d'utilisateur
 * password : Le mot de passe
 * -j : Le mode json
 * -p arg : La profondeur d'exploration
 * -i : Le mode interruption et reprise de panne
 * -e arg : L'exploration profonde
 */
public class Parameters {

    private String username; // Le nom de l'utilisateur
    private String password; // Le mot de passe
    private String url; // l'url de connection
    private String path; // Le chemin actuel
    private String fileToSearch; // Le fichier à rechercher
    private int deep; // La profondeur d'exploration
    private Boolean isJson; // Le mode json
    private Boolean isDeeplyExplore; // Le mode exploration profonde
    private Boolean allowedInterrupt; // Le mode interruption
    private Boolean displayFile; // Le mode d'affichage des fichiers
    private Boolean search; // Le mode de recherche
    private Boolean displayRight; // Le mode d'affichage des droits
    private Boolean displayFolder; // Le mode d'affichage des dossiers

    /**
     * Le constructeur pour la classe Parameters
     */
    public Parameters() {
        this.username = "anonymous";
        this.password = "anonymous";
        this.url = "ftp.ubuntu.com";
        this.deep = 2;
        this.isJson = false;
        this.isDeeplyExplore = true;
        this.allowedInterrupt = false;
        this.path = "/";
        this.displayFile = true;
        this.search = false;
        this.displayRight = false;
        this.displayFolder = true;
        this.fileToSearch = "/";
    }

    /**
     * Modifie l'url de connection
     * 
     * @param url L'url
     */
    public void setUrl(String url) {
        this.url = url;
    }

    /**
     * Modifie le mot de passe de tentative de connexion actuel de l'utilisateur
     * 
     * @param password Le nouveau password
     */
    public void setPassword(String password) {
        this.password = password;
    }

    /**
     * Modifie le nom d'utilisateur actuel
     * 
     * @param username Le nouveau nom
     */
    public void setUser(String username) {
        this.username = username;
    }

    /**
     * Modifie la profondeur d'exploration
     * 
     * @param count Le nombre d'étages
     */
    public void setDeep(int count) {
        this.deep = count;
    }

    /**
     * Active json format
     */
    public void setIsJson() {
        this.isJson = true;
    }

    /**
     * Active l'exploration en profondeur
     */
    public void setDeeplyExplore() {
        this.isDeeplyExplore = true;
    }

    /**
     * Active les interruptions
     * @param allowedInterrupt La valeur à affecter
     */
    public void setAllowedInterrupt(Boolean allowedInterrupt) {
        this.allowedInterrupt = allowedInterrupt;
    }

    /**
     * Modifie le chemin actuel
     * 
     * @param path Le nouveau chemin
     */
    public void setPath(String path) {
        this.path = path;
    }

    /**
     * Active l'affichage des fichiers
     * @param displayFile La valeur à affecter
     */
    public void setDisplayFile(Boolean displayFile) {
        this.displayFile = displayFile;
    }

    /**
     * Active la recherche
     * @param search La valeur à affecter
     * @param path le fichier à chercher
     */
    public void setSearch(Boolean search, String path) {
        this.search = search;
        this.fileToSearch = path;
    }

    /**
     * Active l'affichage des droits
     *@param displayRight La valeur à affecter
     */
    public void setDisplayRight(Boolean displayRight) {
        this.displayRight = displayRight;
    }

    /**
     * Active l'affichage des droits
     * @param displayFolder La valeur à affecter
     */
    public void setDisplayFolder(Boolean displayFolder) {
        this.displayFolder = displayFolder;
    }

    /**
     * Renvoie le nom d'utilisateur
     * 
     * @return le nom d'utilisateur
     */
    public String getUsername() {
        return this.username;
    }

    /**
     * Renvoie le mot de passe de l'utilisateur
     * 
     * @return Le mot de passe
     */
    public String getPassword() {
        return this.password;
    }

    /**
     * Renvoie l'url de connection
     * 
     * @return l'url
     */
    public String getUrl() {
        return this.url;
    }

    /**
     * Renvoie la pronfondeur d'exploration
     * 
     * @return La valeur de profondeur
     */
    public int getDeep() {
        return this.deep;
    }

    /**
     * Renvoie si le format json est activé
     * 
     * @return Le format json est activé ou non
     */
    public Boolean getIsJson() {
        return this.isJson;
    }

    /**
     * Renvoie si l'exploration profonde est activée
     * 
     * @return L'exploration profonde est activée ou non
     */
    public Boolean getIsDeeplyExplore() {
        return this.isDeeplyExplore;
    }

    /**
     * Renvoie le paramètre d'interruption
     * 
     * @return Le paramètre d'interruption
     */
    public Boolean getAllowedInterrupt() {
        return this.allowedInterrupt;
    }

    /**
     * Renvoie le chemin actuel
     * 
     * @return Le chemin actuel
     */
    public String getPath() {
        return this.path;
    }

    /**
     * Renvoie si l'affichage des fichiers est activé
     * 
     * @return L'affichage des fichiers est activé ou non
     */
    public Boolean getDisplayFile() {
        return this.displayFile;
    }

    /**
     * Renvoie si la recherche est activée
     * 
     * @return La recherche est activée ou non
     */
    public Boolean getSearch() {
        return this.search;
    }

    /**
     * Renvoie le chemin de recherche
     * 
     * @return Le chemin de recherche
     */
    public String getPathToSearch() {
        return this.fileToSearch;
    }

    /**
     * Renvoie si l'affichage des droits est activé
     * 
     * @return L'affichage des droits est activé ou non
     */
    public Boolean getDisplayRight() {
        return this.displayRight;
    }

    /**
     * Renvoie si l'affichage des dossiers est activé
     * 
     * @return L'affichage des dossiers est activé ou non
     */
    public Boolean getDisplayFolder() {
        return this.displayFolder;
    }

}
