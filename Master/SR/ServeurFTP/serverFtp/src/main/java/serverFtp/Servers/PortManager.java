/**
 * Classe Port
 * @version 1.0
 * @authors Alexis Bernard et Tom Taffin
 * @file Port.java
 */
package serverFtp.Servers;

import java.util.ArrayList;
import java.util.List;
/**
 * La classe Port qui va gérer les ports utilisée.
 * Celle-ci permet à PASV et PORT de voir quel port sont déja associées à d'autres clients
 */
public class PortManager {
	Long nbport; // nombre de port
	Long capacity; // capacité
	List<Long> list_used_port; // liste des ports utilisés

	/**
	 * Constructeur de la classe Port
	 * @param nbport Le nombre de port
	 * @param capacity La capacité
	 */
	public PortManager(Long nbport, Long capacity) {
		this.nbport = nbport;
		this.capacity = capacity;
		this.list_used_port = new ArrayList<Long>();
	}

	/**
	 * Méthode qui va retourner le nombre de port
	 * @return Le nombre de port
	 */
	public Long getNbport() {
		return nbport;
	}

	/**
	 * Méthode qui va définir le nombre de port
	 * @param nbport Le nombre de port
	 */
	public void setNbport(Long nbport) {
		this.nbport = nbport;
	}

	/**
	 * Méthode qui va retourner la capacité
	 * @return La capacité
	 */
	public Long getCapcity() {
		return capacity; 
	}

	/**
	 * Méthode qui va définir la capacité
	 * @param capacity La capacité
	 */
	public void setCapcity(Long capacity) {
		this.capacity = capacity;
	}

	/**
	 * Méthode qui va retourner la liste des ports utilisés
	 * @return La liste des ports utilisés
	 */
	public List<Long> getList_used_port() {
		return list_used_port; 
	}

	/**
	 * Méthode qui va définir une liste des ports utilisés
	 * @param list_used_port La liste des ports utilisés
	 */
	public void setList_used_port(List<Long> list_used_port) {
		this.list_used_port = list_used_port;
	}

	/**
	 * Méthode qui va ajouter un port à la liste des ports utilisés
	 * @param port Le port à ajouter
	 */
	public void addPort(Long port) {
		this.list_used_port.add(port);
	}

	/**
	 * Méthode qui va supprimer un port de la liste des ports utilisés
	 * @param port Le port à supprimer
	 */
	public void removePort(Long port) {
		this.list_used_port.remove(port);
	}

	/**
	 * Méthode qui va vérifier si les port sont plein
	 * @return boolean
	 */
	public boolean isFull() {
		return this.list_used_port.size() == this.capacity;
	}

	/**
	 * Méthode qui va retourner le prochain port disponible
	 * @return
	 */
	public Long nextPort(){
		Long port = this.nbport;
		while(this.list_used_port.contains(port)){
			port++;
		}
		return port;
	}
}
