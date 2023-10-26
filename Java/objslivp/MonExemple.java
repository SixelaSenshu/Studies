
import java.util.List;
import java.util.Map;

public class MonExemple {

    public static void exempleDLB() {
        ObjVLisp obj = ObjVLispFabrique.nouveau(); // Constructeur

        /**
         * La metaClass est un type de variable qui contient des classes
         * On creer l'instance qui permet de récupèrer les différentes classes
         * qu'elles contient ( c'est la classe Class)
         */
        OObjet metaClass = obj.getClasse("Classe");

        /** Création et initialisation du type véhicule et de ces variables */

        /**
         * Le type Véhicule permet de manipuler des variables de type
         * véhicules
         */
        OObjet vehiculeClass = obj.getClasse("Vehicule");

        // On crée à partir du message ":nouveau" une nouvelle variable de type véhicule

        // une variable de type vehicule qui contient la valeur véhicule
        OObjet vehicule = vehiculeClass.message(":nouveau", "vehicule");

        // une variable de type vehicule qui contient la valeur voiture
        OObjet voiture = vehiculeClass.message(":nouveau", "voiture");

        // une variable de type vehicule qui contient la valeur camion
        OObjet moto = vehiculeClass.message(":nouveau", "moto");

        // une variable de type vehicule qui contient la valeur voiture diesel
        OObjet voitureDiesel = vehiculeClass.message(":nouveau", "voitureDiesel");

        // une variable de type vehicule qui contient la valeur voiture essence
        OObjet voitureEssence = vehiculeClass.message(":nouveau", "voitureEssence");

        /** Création des classes */
        /**
         * * On crée à partir du message :nouveau un methode permetant d'instancier
         * uneclasse
         */

        /**
         * instance de la classe metaClass qui sera la classe Véhicule
         * elle à pour valeur la variable de type vehicule qui a pour valeur vehicule
         * elle retourne comme type sa propre valeur
         */
        OObjet classVehicule = metaClass.message(":nouveau",
                Map.of("nomClasse", "classVehicule"));
        classVehicule.message(":message", "creerVehicule", (Message) (o, a) -> o.message("nouveau"));
        classVehicule.message(":message", "getValue", (Message) (o, a) -> vehicule);
        classVehicule.message(":message", "getType", (Message) (o, a) -> o.message("getValue"));

        /**
         * instance de la classe metaClass qui sera la classe Voiture
         * elle à pour valeur la variable de type vehicule qui a pour valeur voiture
         * elle retourne comme type la valeur de la classe donc elle hérite, autrement
         * dit la variable véhicule
         */
        OObjet classVoiture = metaClass.message(":nouveau",
                Map.of("nomClasse", "classVoiture", "superClasse", vehicule));
        classVoiture.message(":message", "getValue", (Message) (o, a) -> voiture);
        classVoiture.message(":message", "getType", (Message) (o, a) -> o.superMessage("getValue"));

        /**
         * instance de la classe metaClass qui sera la classe Moto
         * elle à pour valeur la variable de type vehicule qui a pour valeur Moto
         * elle retourne comme type la valeur de la classe donc elle hérite, autrement
         * dit la variable véhicule
         */
        OObjet classMoto = metaClass.message(":nouveau",
                Map.of("nomClasse", "classMoto", "superClasse", vehicule));
        classMoto.message(":message", "getValue", (Message) (o, a) -> moto);
        classMoto.message(":message", "getType", (Message) (o, a) -> o.superMessage("getValue"));

        /**
         * instance de la classe metaClass qui sera la classe VoitureDiesel
         * elle à pour valeur la variable de type vehicule qui a pour valeur
         * voitureDiesel
         * elle retourne comme type la valeur de la classe donc elle hérite soit
         * voiture
         */
        OObjet classVoitureDiesel = metaClass.message(":nouveau",
                Map.of("nomClasse", "classVoitureDiesel", "superClasse", voiture));
        classVoitureDiesel.message(":message", "getValue", (Message) (o, a) -> voitureDiesel);
        classVoitureDiesel.message(":message", "getType", (Message) (o, a) -> voiture);

        /**
         * instance de la classe metaClass qui sera la classe VoitureDiesel
         * elle à pour valeur la variable de type vehicule qui a pour valeur
         * voitureEssence
         * elle retourne comme type la valeur de la classe donc elle hérite soit
         * voiture
         */
        OObjet classvoitureEssence = metaClass.message(":nouveau",
                Map.of("nomClasse", "classvoitureEssence", "superClasse", voiture));
        classvoitureEssence.message(":message", "getValue", (Message) (o, a) -> voitureEssence);
        classvoitureEssence.message(":message", "getType", (Message) (o, a) -> voiture);

        /** La classe vehicule à pour type et pour valeur la variable vehicule */
        OObjet vehiculeA = classVehicule.message("nouveau");
        Object valueVehicule = vehiculeA.message("getValue");
        Object typeVehicule = vehiculeA.message("getType");
        assert vehicule.equals(valueVehicule);
        assert vehicule.equals(typeVehicule);

        /** La classe vehicule à pour type et pour valeur la variable vehicule */
        OObjet voitureA = classVehicule.message("nouveau");
        Object valueVoiture = voitureA.message("getValue");
        Object typeVoiture = voitureA.message("getType");
        assert voiture.equals(valueVoiture);
        assert vehicule.equals(typeVoiture);

        /** La classe vehicule à pour type et pour valeur la variable vehicule */
        OObjet motoA = classVehicule.message("nouveau");
        Object valueMoto = motoA.message("getValue");
        Object typeMoto = motoA.message("getType");
        assert moto.equals(valueMoto);
        assert vehicule.equals(typeMoto);

        /** La classe vehicule à pour type et pour valeur la variable vehicule */
        OObjet voitureDieselA = classVehicule.message("nouveau");
        Object valueDiesel = voitureDieselA.message("getValue");
        Object typeDiesel = voitureDieselA.message("getType");
        assert voitureDiesel.equals(valueDiesel);
        assert voiture.equals(typeDiesel);

        /** La classe vehicule à pour type et pour valeur la variable vehicule */
        OObjet voitureEssenceA = classVehicule.message("nouveau");
        Object valueEssence = voitureEssenceA.message("getValue");
        Object typeEssence = voitureEssenceA.message("getType");
        assert voitureEssence.equals(valueEssence);
        assert voiture.equals(typeEssence);
    }

    public static void main(String[] args) {
        exempleDLB();
    }
}
