/**
 * Classe qui a pour fonction d'effectuer les différents types d'appels d'arborecence
 * L'arborescence peut être affichée ou non selon les paramètres de la commande
 * Il y a deux types d'arborescence :
 * - L'arborescence standard qui affiche les dossiers et les fichiers
 * - L'arborescence de recherche qui affiche le fichier trouvés
 * Il y a deux types d'exploration :
 * - L'exploration en profondeur qui explore tous les dossiers
 * - L'exploration en largeur qui explore les dossiers un par un
 * 
 * @author Alexis Bernard
 * @version 1.0
 * @since 1.0
 */

package treeftp.utils;

import java.io.IOException;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.List;

import treeftp.commands.*;
import treeftp.server.Client;
import treeftp.server.ClientRequest;

/**
 * Classe pour la recherche et l'affichage d'arborescence
 */
public class Tree {
    /**
     * Classe privée pour empêcher l'instanciation de la classe
     */
    private Tree() {
    }

    /**
     * Lance l'arborescence selon les paramètres
     * 
     * @param parameters Les paramètres de la commande
     * @param client_cmd Le client pour les commandes
     * @throws IOException          Si une erreur d'entrée ou de sortie survient
     * @throws InterruptedException Si une erreur d'interruption survient
     */
    public static void start(Parameters parameters, Client client_cmd) throws IOException, InterruptedException {
        if (parameters.getSearch()) {
            searchTree(parameters.getPath(), 1, client_cmd, parameters);
            
        } else if (parameters.getIsDeeplyExplore()) {
            String space ="";
            if(parameters.getIsJson()){
                System.out.println("{");
                System.out.println("  \"" + parameters.getPath() + "\" : {");
                space = "  ";
            }else{
                System.out.println(parameters.getPath());
            }
            standardTree(parameters.getPath(), 0, client_cmd, parameters, space);
            if(parameters.getIsJson()){
                System.out.println("\n}");
            }
        } else {

        }

    }

    /**
     * Lance l'arborescence de recherche
     * 
     * @param path       Le chemin du dossier
     * @param deep       La profondeur de l'arborescence
     * @param client_cmd Le client pour les commandes
     * @param parameters Les paramètres de la commande
     * @return Si l'arboresence doit encore être explorée
     * @throws IOException          Si une erreur d'entrée ou de sortie survient
     * @throws InterruptedException Si une erreur d'interruption survient
     */
    private static boolean searchTree(String path, int deep, Client client_cmd, Parameters parameters)
            throws IOException, InterruptedException {

        if (deep > parameters.getDeep()) {
            return false;
        }
        ClientRequest requestHandlerCmd;
        List<String> list = new ArrayList<String>();
        List<String> file = new ArrayList<String>();

        // Recupère les fichiers et les dossiers
        requestHandlerCmd = client_cmd.getConnection().getRequest();
        String result = requestList(client_cmd,parameters,path);

        // Créer les listes de fichiers et de dossiers à partir du résultat de la requête
        for (String string : result.split("\n")) {
            if (string.charAt(0) == 'd') {
                String line;
                line = string.split(" ")[string.split(" ").length - 1];
                if (parameters.getDisplayRight() && !parameters.getIsJson()) {
                    line = "(" + string.split(" ")[0] + ") " + line;
                }
                list.add(line);
            } else if (string.charAt(0) == '-' || string.charAt(0) == 'l') {
                String line;
                line = string.split(" ")[string.split(" ").length - 1];
                if (parameters.getDisplayRight() && !parameters.getIsJson()) {
                    line = "(" + string.split(" ")[0] + ") " + line;
                }
                file.add(line);
            }
        }

        // Si il n'y a pas de fichiers ou de dossiers, on arrête l'exploration
         if (file.size() == 0 && list.size() == 0) {
            return false;
        }
        
        // On cheche le fichier dans les fichiers
        if (parameters.getSearch()) {
            for (String line : file) {
                if(line.contains(parameters.getPathToSearch())) {
                    System.out.print(path + "\\" + line + "\n");
                }
            }
        }
    
        // On continue la recherche avec les dossiers
        System.err.println(list);
        for (String line : list) {
            if (path.charAt(path.length() - 1) != '/') {
                path += "/";
            }
            // client_cmd.getConnection().getRequest().changeRepository(line);
            searchTree(path + line, deep + 1, client_cmd,
                        parameters);
            // client_cmd.getConnection().getRequest().changeParentRepository();
        }
        return true;
    }

    /**
     * Lance l'arborescence standard
     * 
     * @param path       Le chemin du dossier
     * @param deep       La profondeur de l'arborescence
     * @param client_cmd Le client pour les commandes
     * @param parameters Les paramètres de la commande
     * @param space      La separation entre les dossiers sous forme de chaine de
     *                   caractères
     * @return Si l'arboresence doit encore être explorée
     * @throws IOException          Si une erreur d'entrée ou de sortie survient
     * @throws InterruptedException Si une erreur d'interruption survient
     */
    private static Boolean standardTree(String path, int deep, Client client_cmd, Parameters parameters, String space)
            throws IOException, InterruptedException, UnknownHostException {
        
        if (deep > parameters.getDeep()) {
            return false;
        }

        ClientRequest requestHandlerCmd;
        List<String> list = new ArrayList<String>();
        List<String> file = new ArrayList<String>();


        // Recupère les fichiers et les dossiers
        requestHandlerCmd = client_cmd.getConnection().getRequest();
        String result = requestList(client_cmd,parameters,path);
        if(result.equals("false")){
            return false;
        }
        
        int count = 1;
        String oldLink = "";
        // Créer les listes de fichiers et de dossiers à partir du résultat de la requête
        for (String string : result.split("\n")) {
            if (string.charAt(0) == 'd') {
                String line;
                line = string.split(" ")[string.split(" ").length - 1];
                if (parameters.getDisplayRight() && !parameters.getIsJson()) {
                    line = "(" + string.split(" ")[0] + ") " + line;
                }
                list.add(line);
            } else if (string.charAt(0) == '-' || string.charAt(0) == 'l') {
                String line;
                line = string.split(" ")[string.split(" ").length - 1];
                if (parameters.getDisplayRight() && !parameters.getIsJson()) {
                    line = "(" + string.split(" ")[0] + ") " + line;
                }
                if(string.charAt(0) == 'l'){
                    if(line.equals(oldLink)){
                        count ++;
                    }else{
                        count = 1;
                    }
                    oldLink = line;
                    file.add(line+"("+count+").link");
                }else{
                    file.add(line);
                }
            }
        }

        // Si il n'y a pas de fichiers ou de dossiers, on arrête l'exploration
        if (file.size() == 0 && list.size() == 0) {
            return false;
        }

        // On affiche les dossiers et les fichiers
        toStringTree(parameters,space,list,file,path,deep,client_cmd);
        

        return true;
    }

    /**
     * Lance la requête LIST et tous les processus de connection
     * @param requestHandlerCmd Le client pour les commandes
     * @param parameters Les paramètres de la commande
     * @param path Le chemin du dossier
     * @return Le résultat de la requête LIST
     * @throws IOException Les erreurs d'entrée et de sortie
     * @throws InterruptedException Les erreurs d'interruption
     */
    private static String requestList(Client client_cmd,Parameters parameters,String path) throws IOException, InterruptedException{
        String params[] = { parameters.getUsername() };
        ClientRequest requestHandlerData , requestHandlerCmd;
        Client client_data;
        requestHandlerCmd = client_cmd.getConnection().getRequest();
        String port_res = requestHandlerCmd.PASV();
        if (port_res == null) {
            return "false";
        }
        client_data = new Client(parameters.getUrl(), Integer.valueOf(port_res),
                parameters.getUsername(), parameters.getPassword());
        if (!requestHandlerCmd.ping()) {
            return "false";
        }
        try{
            client_data.getConnection().connect();
        }catch(Exception e){
                return "false";        
        }
        requestHandlerData = client_data.getConnection().getRequest();
        requestHandlerData.writeRequest("USER", params);
        requestHandlerData.sendRequest();
        params[0] = parameters.getPassword();
        requestHandlerData.writeRequest("PASS", params);
        requestHandlerData.sendRequest();
        requestHandlerCmd.showRepository(path);
        String result = requestHandlerData.readAllRequest();
        requestHandlerCmd.readRequest();
        requestHandlerCmd.readRequest();
        requestHandlerData.disconnect();
        client_data.getConnection().disconnect();
        return result;
    }

    /**
     * Affiche les dossiers
     * @param parameters Les paramètres de la commande
     * @param space La separation entre les dossiers sous forme de chaine de caractères
     * @param list La liste des dossiers
     * @param file La liste des fichiers
     * @param path Le chemin du dossier
     * @param deep La profondeur de l'arborescence
     * @param client_cmd Le client pour les commandes
     * @throws InterruptedException Les erreurs d'interruption
     * @throws IOException Les erreurs d'entrée et de sortie
     * @throws UnknownHostException Les erreurs d'hôte inconnu
     */
    private static void toStringTree(Parameters parameters,String space,List<String> list,List<String> file,String path,int deep,Client client_cmd) throws UnknownHostException, IOException, InterruptedException{
        String addSpace = "|     ";
        Boolean isLast = false;
        System.err.println(list);
        for (String line : list) {
            if (!parameters.getIsJson()) {
                if (parameters.getDisplayFolder()) {
                    System.out.println(space + "|___" + line + "/");
                } else {
                    System.out.println(space + "|_____");
                }
                if (line == list.get(list.size() - 1)) {
                    isLast = true;
                    addSpace = "      ";
                    if (parameters.getDisplayFile()) {
                        if (file.size() == 0) {
                            addSpace = "      ";
                        } else {
                            addSpace = "|     ";
                        }
                    }

                }
            } else {
                if (line == list.get(list.size() - 1)) {
                    isLast = true;
                }
                addSpace = "    ";
                if(file.size() == 0 && list.size() == 0)  {
                    System.out.println(space + "\"" + line + "\":{}");
                }else{
                    System.out.println(space + "\"" + line + "\":{");
                }
            }
            if (path.charAt(path.length() - 1) != '/') {
                path += "/";
            }
            // client_cmd.getConnection().getRequest().changeRepository(line);
            if (parameters.getDisplayRight()) {
                standardTree(path + line.split(" ")[1], deep + 1, client_cmd,
                        parameters, space + addSpace);
            } else {
                standardTree(path + line, deep + 1, client_cmd,
                        parameters, space + addSpace);
            }
            // client_cmd.getConnection().getRequest().changeParentRepository();
            if (parameters.getIsJson()) {   
                if (isLast && file.size() == 0) {
                    System.out.println(space + "}");
                } else {
                    System.out.println(space + "},");                
                }
            }
        }
        toStringFile(parameters,space,file,isLast,path);
    }

    /**
     * Affiche les fichiers
     * @param parameters Les paramètres de la commande
     * @param space La separation entre les dossiers sous forme de chaine de caractères    
     * @param file La liste des fichiers
     * @param isLast Si c'est le dernier dossier
     */
    private static void toStringFile(Parameters parameters,String space,List<String> file,Boolean isLast, String path){
        if (parameters.getDisplayFile()) {
            if (parameters.getIsJson()) {
                if (file.size() >= 1 && parameters.getDisplayFile()) {
                    for (String line : file) {
                        if(line == file.get(file.size() - 1))
                        System.out.println(space + "\"" + line + "\":\"" + path + line + "\"");
                        else
                        System.out.println(space + "\"" + line + "\":\"" + path + line + "\",");            
                    }
                }
            } else {
                for (String line : file) {
                    if (line == file.get(file.size() - 1)) {
                        if (!isLast) {
                            System.out.println(space + "   " + line);
                        } else {
                            System.out.println(space + "|__" + line);
                        }
                    } else {
                        System.out.println(space + "|__" + line);
                    }
                }
                if (isLast) {
                    System.out.println(space);
                }
            }
        }
    }
}
