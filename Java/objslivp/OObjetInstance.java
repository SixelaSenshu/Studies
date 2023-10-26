import java.util.HashMap;
import java.util.List;
import java.util.Map;

class OObjetInstance implements OObjet {

    private Map<String, Object> map;

    OObjetInstance(String nomClasse, OObjet classe, OObjet superClasse, List<String> nomsAttributs,
            Map<String, Object> valeursAttributs, Map<String, Message> methodesClasse) {
        this.map = new HashMap<String, Object>();
        this.map.put("nomClasse", nomClasse);
        this.map.put("classe", classe);
        this.map.put("methodesClasse", methodesClasse);
        this.map.put("superClasse", superClasse);
        this.map.put("valeursAttributs", valeursAttributs);
        this.map.put("nomsAttributs", nomsAttributs);
    }

    public OObjetInstance(Map<String, Object> map) {
        this.map = map;
    }

    @Override
    public <T> T message(String nom, Object... arguments) {
        T result = null;
        Message messageget = null, newMessage = null;
        Map<String, Message> messages = null;
        Map<String, Object> values = null;
        OObjet obj, classe;
        if (this.map.containsKey("methodesClasse")) {
            messages = (Map<String, Message>) this.map.get("methodesClasse");
            if (messages != null) {
                messageget = messages.get(nom);
                if (nom == "getMessage") {
                    newMessage = (Message) messageget.apply(this, this.map, arguments);
                    if (newMessage != null)
                        return (T) newMessage;
                    else
                        messageget = null;
                }
            }
        }
        if (this.map.containsKey("classe") && messageget == null) {
            obj = (OObjet) this.map.get("classe");
            if (obj != null) {
                if (nom != "getMessage") {
                    messageget = obj.message("getMessage", nom);
                } else {
                    messageget = obj.message(nom, arguments);
                }
            }
        }
        if (this.map.containsKey("superClasse") && messageget == null) {
            classe = (OObjet) map.get("superClasse");
            if (classe != null) {
                if (nom != "getMessage")
                    messageget = classe.message("getMessage", nom);
                else
                    messageget = classe.message(nom, arguments);
            }
        }
        if (messageget != null) {
            values = (Map<String, Object>) this.map.get("valeursAttributs");
            if (this.map.get("valeursAttributs") != null) {
                if (values.containsKey(nom) || values.containsKey(nom.subSequence(1, nom.length()))) {
                    return (T) messageget.apply(this, this.map, nom, arguments);
                }
            }
            if (nom == "getMessage") {
                return (T) messageget;
            }
            result = (T) messageget.apply(this, this.map, arguments);
        }
        return result;
    }

    @Override
    public <T> T superMessage(String nom, Object... arguments) {

        T result = null;
        Message messageget = null, newMessage = null;
        Map<String, Message> messages = null;
        Map<String, Object> values = null;
        OObjet obj, classe;
        if (this.map.containsKey("methodesClasse")) {
            messages = (Map<String, Message>) this.map.get("methodesClasse");
            if (messages != null) {
                messageget = messages.get(nom);
                if (nom == "getMessage") {
                    newMessage = (Message) messageget.apply(this, this.map, arguments);
                    if (newMessage != null)
                        return (T) newMessage;
                    else
                        messageget = null;
                }
            }
        }
        if (this.map.containsKey("superClasse") && messageget == null) {
            obj = (OObjet) this.map.get("superClasse");
            if (obj != null) {
                if (nom != "getMessage") {
                    messageget = obj.superMessage("getMessage", nom);
                } else {
                    messageget = obj.superMessage(nom, arguments);
                }
            }
        }
        if (this.map.containsKey("classe") && messageget == null) {
            classe = (OObjet) map.get("classe");
            if (classe != null) {
                if (nom != "getMessage")
                    messageget = classe.superMessage("getMessage", nom);
                else
                    messageget = classe.superMessage(nom, arguments);
            }
        }
        if (messageget != null) {
            if (nom == "getMessage") {
                return (T) messageget;
            } else {
                result = (T) messageget.apply(this, this.map, arguments);
            }
        }
        return result;
    }

    @Override
    public <T> T error(String cause) {
        T result = null;
        System.err.println(cause);
        return result;
    }
}
