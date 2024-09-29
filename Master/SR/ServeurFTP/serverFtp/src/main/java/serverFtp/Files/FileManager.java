/**
 * @file FileManager.java
 * @brief Contient la classe FileManager qui va gérer les fichiers
 * @version 1.0
 * @authors Alexis Bernard & Tom Taffin
 */

package serverFtp.Files;

import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.attribute.PosixFileAttributes;
import java.nio.file.attribute.PosixFilePermissions;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

/**
 * Classe FileManager qui va gérer les fichiers
 */
public class FileManager {
    
	/**
	 * Constructeur de la classe FileManager
	 */
    private FileManager() {} 

    /**
	 * Récupère les informations d'un fichier ( droits, taille, date, nom, ...)
	 * @param file Le fichier
	 * @return String
	 */
    static public String getInfos(File file) {
        Path filePath = file.toPath();
        try {
            PosixFileAttributes attrs = Files.readAttributes(filePath, PosixFileAttributes.class);
            String permissions = PosixFilePermissions.toString(attrs.permissions());
            String date = new SimpleDateFormat("MMM dd HH:mm").format(new Date(attrs.lastModifiedTime().toMillis()));
            String fileType = file.isDirectory() ? "d" : "-";
            return String.format("%s%s %3d %-8d %-8d %8d %s %s",
                    fileType,
                    permissions,
                    attrs.fileKey().hashCode(), 
                    attrs.owner().hashCode(),
                    attrs.group().hashCode(),   
                    attrs.size(),
                    date,
                    filePath.getFileName());
        } catch (Exception e) {
            System.err.println("Error while displaying files");
			return null;
        }
    }


	/**
	 * Récupère Les informations de tous les fichiers d'un dossier
	 * @param path Le chemin du dossier
	 * @return La liste des informations
	 */
	static public List<String> getLines(String path) {
        String infos;
        List<String> lines = new ArrayList<>();
        File dir = new File(path);
        File[] files = dir.listFiles();
        for(File file : files) {
            infos = FileManager.getInfos(file) + "\r\n";
            lines.add(infos);
        }
        return lines;
    }

	/**
	 * Assemble des chaînes de chemin vers un fichier
	 * @param str les chaînes séparées
	 * @return Les chaines assemblées
	 */
	static private String join(String... str) {
		String res = "";
		for (String path : str) {
			String thePath = path;
			while (thePath.length() != 0 && thePath.charAt(thePath.length() - 1) == '/') thePath = thePath.substring(0, thePath.length() - 1);
			res += "/" + thePath;
		}
		return res.substring(1);
	}

	/**
	 * Récupère le nouveau chemin après un déplacement si possible
	 * @param path Le chemin actuel
	 * @param root Le chemin racine
	 * @param toGo Le chemin à ajouter
	 * @return Le nouveau chemin
	 */
    static public String moveIfPossible(String path, String root, String toGo) {
        String pathWhenMoving;
		String move = toGo;
		// Analyse si le chemin est absolu ou relatif
        if (move.substring(0, 1).equals("/")) {
			move = move.substring(1);
            pathWhenMoving = "";
        }else{
			System.out.println(move);
			pathWhenMoving = path;
		}
		// Récupère le chemin sous forme de tableau
        String[] splitMove = move.split("/");
		int count = -1;
		// Parcours le chemin pour trouver le dossier
        for(String folderPath : splitMove) {
			count++;
			// Si le chemin est vide ou égal à un point, on passe au suivant
			if (splitMove[count].equals("") || splitMove[count].equals(".")){
				continue;
			}
			File folder = new File(FileManager.join(root, pathWhenMoving));
			boolean haveFound = false;
			// Si le chemin est égal à deux points, on remonte d'un dossier
			if (splitMove[count].equals("..")) {
				String[] splitPath = pathWhenMoving.split("/");
				if (splitPath.length == 0) {pathWhenMoving = "/"; continue;}
				String toRemove = splitPath[splitPath.length - 1];
				splitPath = pathWhenMoving.split("/" + toRemove);
				if (splitPath.length == 0) pathWhenMoving = "/";
				else pathWhenMoving = splitPath[0];
				continue;
			}
			// Sinon, on parcourt les fichiers du dossier
			for(File file : folder.listFiles()) {
				System.out.println(file.toString());
				if(file.isDirectory()){
					if(file.getName().equals(folderPath)){
						pathWhenMoving = FileManager.join(pathWhenMoving, folderPath);
						haveFound = true;
						break;
					}
				}
			}
			if (!haveFound) return null;
        }
        return pathWhenMoving;
    }

	/**
	 * Crée un dossier si possible
	 * @param path Le chemin
	 * @param dir Le dossier
	 * @param root Le chemin racines
	 * @return Le code de retour
	 */
	static public Boolean createDirIfPossible(String path, String dir, String root){
		File folder = new File(root + path + "/" + dir);
		if (!folder.exists()) {
			folder.mkdir();
			return true;
		}
		return false;
	}

	/**
	 * Supprime un dossier si possible
	 * @param path Le chemin
	 * @param dir Le dossier
	 * @param root Le chemin racines
	 * @return Le code de retour
	 */
	static public int removeDirIfPossible(String path, String dir, String root){
		File folder = new File(root + path + "/"+  dir);
		if (folder.exists()){
			if(folder.list().length == 0) {
				folder.delete();
				return 0;
			}
			return 1;
		}
		return 2;
	}

	/**
	 * Recherche un contenu si possible
	 * @param path Le chemin
	 * @param file Le fichier
	 * @param root Le chemin racines
	 * @return Le code de retour
	 */
	static public String searchFileIfPossible(String path, String file, String root){
		File folder = new File(root + path + "/" + file);
		if (folder.exists()) return folder.getPath();
		return null;
	}

	/**
	 * Renomme un contenu si possible
	 * @param path Le chemin 
	 * @param oldName L'ancien nom
	 * @param newName Le nouveau nom
	 * @param root Le chemin racines
	 * @return Le code de retour
	 */
	static public int renameContentIfPossible(String path, String oldName, String newName, String root){
		File oldFolder = new File(oldName);
		File newFolder = new File(FileManager.join(root, path, newName));
		if (oldFolder.exists() && !newFolder.exists()) {
			String[] list = oldFolder.list();
			if(list != null) return 1;
			oldFolder.renameTo(newFolder);
			return 0;
		}
		if (newFolder.exists()) return 1;
		return 2;
	}

	/**
	 * Efface un contenu si possible
	 * @param path Le chemin
	 * @param root Le chemin racines
	 * @param file Le fichier
	 * @return
	 */
	static public Boolean deleteContentIfPossible(String path, String root, String file){
		File file_to_delete = new File(root + path + "/" + file);
		System.out.println(file_to_delete);
		if(file_to_delete.exists()){
			file_to_delete.delete();
			return true;
		}
		return false;
	}

	/**
     * Crée un fichier si possible
     * @param path Le chemin
     * @param file Le fichier
     * @param root Le chemin racines
     * @return Le code de retour
     */
    static public Boolean createFileIfPossible(String path, String file, String root){
        File file_to_create = new File(root + path + "/" + file);
        if (!file_to_create.exists()) {
            try {
                file_to_create.createNewFile();
                return true;
            } catch (Exception e) {
                System.err.println("Error while creating file");
                return false;
            }
        }
        return false;
    }

    /**
     * Récupère un fichier si possible et permet le téléchargement
     * @param path Le chemin
     * @param file Le fichier
     * @param root Le chemin racines
     * @return Le fichier
     */
    static public File retrieveFileIfPossible(String path, String file, String root){
        File file_to_retrieve = new File(root + path + "/" + file);
        if (file_to_retrieve.exists()) {
            return file_to_retrieve;
        }
        return null;
    }

	static public String getSizeIfPossible(String path, String file,String root){
		File file_to_find = new File(root + path + "/" + file);
		if (file_to_find.exists()) {
			return String.valueOf(file_to_find.length());
		}
		return root;
	}
}