
/**
 * @brief Interface ObjVLisp qui est l'environnement du langage.
 *        Permet de récupérer et créer des metaclasses, des classes ( qui sont
 *        des instances de metaclasses ) ainsi que des instances de classes.
 */
interface ObjVLisp {
    /**
     * Permet de récupérer un OObject ( Plus précisement une classe ).
     * 
     * @param nomDeClasse Le nom de la classe
     * @return L'OObjet créer ou déja présent
     */
    OObjet getClasse(String nomDeClasse);
}