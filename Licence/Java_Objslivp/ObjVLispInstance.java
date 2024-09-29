import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

/**
 * @brief Class qui implémente l'interface ObjVLisp
 *        Elle contient toutes les classes spécifiques pour créer des objets,des
 *        classes et métaclasses.
 */
class ObjVLispInstance implements ObjVLisp {

    /**
     * @brief Map qui contient tous les classes spécifiques.
     */
    private Map<String, OObjet> objects;

    /**
     * @brief constructor de ObjVLispInstance
     */
    ObjVLispInstance() {
        //// Creation des map permettant de stocker les informations pour les 3 classes
        //// principales.
        Map<String, Message> metaClassMessages = new HashMap<String, Message>(),
                rootObjectMessages = new HashMap<String, Message>(),
                systemClassMessages = new HashMap<String, Message>();

        //// Les OObjet qui récupéreront les outils de l'environnement.
        OObjet metaClass, rootObjet, systemClass;

        /// L'ensemble des fonctions qui seront implémenté dans le langage
        Message addMessage, DnouveauM, nouveauO, afficher, toString, acceptMessage;

        /// La map qui contient toutes les classes.
        this.objects = new HashMap<String, OObjet>();

        rootObjet = new OObjetInstance("rootObject,", null, null, null, null, rootObjectMessages);
        metaClass = new OObjetInstance("metaClass", null, rootObjet, null, null, metaClassMessages);
        systemClass = new OObjetInstance("systemClass,", null, null, null, null, systemClassMessages);

        // Message qui permet de récupérer une fonction d'une instance OObjet
        Message getMessage = (Message) (OObjet o, Object[] a) -> {
            Map<String, Object> attributs = (Map<String, Object>) a[0];
            Map<String, Message> messages = (Map<String, Message>) attributs.get("methodesClasse");
            Object[] addArguments = (Object[]) a[1];
            if (messages.containsKey((String) addArguments[0])) {
                return messages.get(addArguments[0]);
            }
            return null;
        };

        metaClassMessages.put("getMessage", getMessage);
        rootObjectMessages.put("getMessage", getMessage);
        systemClassMessages.put("getMessage", getMessage);

        // Message qui permet de récupérer les proprietées d'une instance OObjet
        Message getProperties = (Message) (OObjet o, Object[] a) -> {
            Map<String, Object> attributs = (Map<String, Object>) a[0];
            if (a[0] == null) {
                return null;
            }
            return attributs;
        };

        // Permet de dire si un message est dans la classe ou non et si l'object peut
        // l'ajouter
        acceptMessage = (Message) (OObjet o, Object[] a) -> {
            if (a.length != 2) {
                o.error("Pas assez ou trop de paramètres pour valider le nom du message");
                return false;
            }

            Map<String, Object> objects = (Map<String, Object>) a[0];
            Map<String, Message> methods = (Map<String, Message>) objects.get("methodesClasse");
            Object[] objs = (Object[]) a[1];
            if (methods == null) {
                o.error("[WARNING] Fonction " + objs[2] + " n'est pas applicable car l'objet n'est pas une metaClasse");
                return false;
            }
            if (methods.containsKey(objs[2])) {
                o.error("[UPDATE] Fonction " + objs[2] + " Déja dans la classe : redéfinition");
                return true;
            }

            return true;
        };
        metaClassMessages.put(":accept", acceptMessage);

        // Permet d'ajouter un message dans un OObject
        addMessage = (Message) (OObjet o, Object[] a) -> {
            Object[] addArguments = (Object[]) a[1];
            if (a.length != 2)
                return o.error("[WARNING] Pas assez de paramètres pour inserer le nom du message.\n");
            if (!(Boolean) o.message(":accept", a[0], addArguments[1], addArguments[0]))
                return o.error("[WARNING] La methode est déja présente ou invalide.\n");
            Map<String, Object> objects = (Map<String, Object>) a[0];
            Map<String, Message> methods = (Map<String, Message>) objects.get("methodesClasse");
            Message m = (Message) addArguments[1];
            String name = (String) addArguments[0];
            methods.put(name, m);
            return true;
        };
        metaClassMessages.put(":message", addMessage);

        // Permet de créer un nouveau OObjet qui est une metaClasse
        // Celui-ci créer par défaut les getters et setters de la classe
        DnouveauM = (Message) (OObjet unObjet, Object[] arg) -> {
            Map<String, Object> arguments = null;
            Map<String, Object> objects = null;
            List<String> nomsAttributs = null;
            OObjet superClasse = null;
            Map<String, Message> methods = null;
            objects = (Map<String, Object>) arg[0];
            Object[] args = (Object[]) arg[1];
            arguments = (Map<String, Object>) args[0];
            if (arguments == null) {
                return unObjet.error("[WARNING] Pas d'arguments pour la création d'une nouvelle metaclasse\n");
            }
            if (arguments.containsKey("superClasse"))
                superClasse = (OObjet) arguments.get("superClasse");
            if (arguments.containsKey("nomsAttributs")) {
                nomsAttributs = (List<String>) arguments.get("nomsAttributs");
            }
            methods = new HashMap<String, Message>();
            methods.put("getMessage", getMessage);
            methods.put("getProperties", getProperties);

            OObjet obj = new OObjetInstance((String) arguments.get("nomClasse"), metaClass,
                    superClasse,
                    nomsAttributs, null, methods);
            if (nomsAttributs != null) {
                for (int i = 0; i < nomsAttributs.size(); i++) {
                    obj.message(":message", ":" + (String) nomsAttributs.get(i),
                            (Message) (OObjet o,
                                    Object[] a) -> {
                                Map<String, Object> map = (Map<String, Object>) a[0];
                                Object[] argumentSet = (Object[]) a[2];
                                Map<String, Object> values = (Map<String, Object>) map.get("valeursAttributs");
                                String name = (String) a[1];
                                String nameWithoutSpecial = name.substring(1, name.length());
                                values.put(nameWithoutSpecial, argumentSet[0]);
                                return true;
                            });

                    obj.message(":message", (String) nomsAttributs.get(i), (Message) (OObjet o,
                            Object[] a) -> {
                        Map<String, Object> map = (Map<String, Object>) a[0];
                        String name = (String) a[1];
                        Object[] argumentGet = (Object[]) a[2];
                        Map<String, Object> values = (Map<String, Object>) map.get("valeursAttributs");
                        return values.get(name);
                    });
                }
            }
            objects.put((String) arguments.get("nomClasse"), obj);
            return obj;

        };
        metaClassMessages.put(":nouveau", DnouveauM);

        // Créer une nouvelle instance
        nouveauO = (OObjet o, Object[] a) -> {
            Map<String, Object> m = (Map<String, Object>) a[0];
            Map<String, Object> l = new HashMap<String, Object>();
            List<String> name = (List<String>) m.get("nomsAttributs");
            if (name != null) {
                for (int i = 0; i < name.size(); i++) {
                    l.put(name.get(i), null);
                }
            }
            OObjet obj = new OObjetInstance("Instance" + m.get("nomClasse"), o, null, null, l, null);
            return obj;
        };
        rootObjectMessages.put("nouveau", nouveauO);

        // Affiche dans la console une instance Object
        afficher = (o, a) -> {
            if (a == null) {
                o.error("[WARNING] Pas d'arguments pour afficher sur la console\n");
                return false;
            }
            Object[] s = (Object[]) a[1];
            System.out.println(s[0]);
            return true;
        };
        systemClassMessages.put(":afficher", afficher);

        // Retourne en String les données d'un OObjet
        toString = (Message) (OObjet o, Object[] a) -> {
            StringBuilder sb = new StringBuilder();
            Map<String, Object> objects = (Map<String, Object>) a[0];
            if (objects.get("nomClasse") != null)
                sb.append("NomClasse : " + objects.get("nomClasse") + "\n");
            if (objects.get("classe") != null)
                sb.append("Classe : " + objects.get("classe") + "\n");
            if (objects.get("superClasse") != null)
                sb.append("SuperClasse : " + objects.get("superClasse") + "\n");
            if (objects.get("nomsAttributs") != null) {
                sb.append("nomsAttributs : " + objects.get("nomsAttributs") + "\n");
            }
            if (objects.get("valeursAttributs") != null) {
                Map<String, Object> att = ((Map<String, Object>) objects.get("valeursAttributs"));
                sb.append("valeursAttributs : {");
                for (Map.Entry<String, Object> item : att.entrySet()) {
                    sb.append("[" + item.getKey() + ":" + item.getValue() + "]");
                }
                sb.append("}\n");
            }
            if (objects.get("methodesClasse") != null) {
                Map<String, Message> msg = ((Map<String, Message>) objects.get("methodesClasse"));
                sb.append("methodesClasse : {");
                for (Map.Entry<String, Message> item : msg.entrySet()) {
                    sb.append("[" + item.getKey() + "]");
                }
                sb.append("}\n");
            }

            return sb.toString();
        };
        rootObjectMessages.put("toString", toString);
        this.objects.put("Class", metaClass);
        this.objects.put("Object", rootObjet);
        this.objects.put("System", systemClass);

    }

    @Override
    public OObjet getClasse(String nomDeClasse) {
        OObjet objet;
        Set<String> keys = objects.keySet();
        if (keys.contains(nomDeClasse)) {
            objet = objects.get(nomDeClasse);
        } else {
            OObjet newObject = new OObjetInstance(nomDeClasse, this.objects.get("Class"), this.objects.get("Object"),
                    new ArrayList<String>(),
                    new HashMap<String, Object>(), new HashMap<String, Message>());
            objet = newObject;
            objects.put(nomDeClasse, objet);
        }
        return objet;
    }

}
