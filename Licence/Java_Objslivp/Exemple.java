import java.util.List;
import java.util.Map;

public class Exemple {
        public static void main(String[] args) {
                ObjVLisp obj;
                OObjet metaClass, system, object, metaPoint, point, metaInt, pointWithValues, int1;

                obj = ObjVLispFabrique.nouveau();
                System.out.println(
                                "________________________________________________________________________________________________________ Début ____________________________________________________________________________________________________");
                metaClass = obj.getClasse("Class");
                system = obj.getClasse("System");
                object = obj.getClasse("Object");
                System.out.println(
                                "------------------------------------------------ Les classes primitives ----------------------------------------\n");
                system.message(":afficher", (String) object.message("toString"));
                system.message(":afficher", (String) metaClass.message("toString"));

                System.out.println(
                                "------------------------------------------------ La Classe Point -----------------------------------------------\n");
                metaPoint = metaClass.message(":nouveau", Map.of("nomClasse",
                                "Point", "nomsAttributs", List.of("x", "y")));

                system.message(":afficher", (String) metaPoint.message("toString"));

                point = metaPoint.message("nouveau");
                system.message(":afficher", (String) point.message("toString"));
                point.message(":x", 1);
                system.message(":afficher", (String) point.message("toString"));

                pointWithValues = metaPoint.message("nouveau");
                pointWithValues.message(":x", 10);
                pointWithValues.message(":y", 20);

                metaPoint.message(":message", "Sum",
                                (Message) (o, a) -> (Integer) o.message("x") + (Integer) o.message("y"));

                system.message(":afficher", (String) metaPoint.message("toString"));

                system.message(":afficher", (Object) pointWithValues.message("toString"));

                system.message(":afficher", "La somme est : " + (Object) pointWithValues.message("Sum"));

                System.out.println(
                                "------------------------------------------------ La Classe Int ------------------------------------------------\n");
                metaInt = metaClass.message(":nouveau", Map.of(
                                "nomClasse",
                                "Int", "nomsAttributs", List.of("v")));

                system.message(":afficher", (String) metaInt.message("toString"));

                metaInt.message(":message", "False", (Message) (o, a) -> 0);
                metaInt.message(":message", "False", (Message) (o, a) -> 0);

                int1 = metaInt.message("nouveau");
                system.message(":afficher", (String) int1.message("toString"));

                System.out.println(
                                "------------------------------------------------Exemple du projet ------------------------------------------------\n");

                OObjet classA = metaClass.message(":nouveau", Map.of("nomClasse", "A"));
                classA.message(":message", "foo", (Message) (o, a) -> 10);
                classA.message(":message", "bar", (Message) (o, a) -> o.message("foo"));
                OObjet classB = metaClass.message(":nouveau",
                                Map.of("nomClasse", "B", "superClasse", classA));
                classB.message(":message", "bar",
                                (Message) (o, a) -> (Integer) o.superMessage("bar") + (Integer) o.message("foo"));
                OObjet classC = metaClass.message(":nouveau",
                                Map.of("nomClasse", "C", "superClasse", classB));
                classC.message(":message", "foo", (Message) (i, a) -> 50);
                OObjet anA = classA.message("nouveau");
                OObjet aB = classB.message("nouveau");
                OObjet aC = classC.message("nouveau");
                system.message(":afficher", (Object) classA.message("toString"));
                system.message(":afficher", (Object) classB.message("toString"));
                system.message(":afficher", (Object) classC.message("toString"));
                // system.message(":afficher", "Le resultat de bar est : " + (Object)
                // anA.message("bar"));
                // system.message(":afficher", "Le resultat de bar est : " + (Object)
                // aB.message("bar"));
                // system.message(":afficher", "Le resultat de bar est : " + (Object)
                // aC.message("bar"));
                // System.out.println(
                // "------------------------------------------------Classe Boolean
                // ------------------------------------------------\n");

                // OObjet metaBoolean = metaClass.message(":nouveau", Map.of("nomClasse",
                // "Boolean", "nomsAttributs", List.of("value")));

                // metaBoolean.message(":message", "not", (Message) (o, a) -> false);
                // metaBoolean.message(":message", "or", (Message) (o, a) -> false);
                // metaBoolean.message(":message", "and", (Message) (o, a) -> false);

                // OObjet metaAnd = metaClass.message(":nouveau", Map.of("nomClasse",
                // "And", "superClasse", metaBoolean, "nomsAttributs", List.of("value",
                // "value2")));

                // OObjet metaOr = metaClass.message(":nouveau", Map.of("nomClasse",
                // "And", "superClasse", metaBoolean, "nomsAttributs", List.of("value",
                // "value2")));

                // OObjet metaNot = metaClass.message(":nouveau", Map.of("nomClasse",
                // "And", "superClasse", metaBoolean, "nomsAttributs", List.of("value")));

                // system.message(":afficher", (Object) metaBoolean.message("toString"));

                // system.message(":afficher", (Object) metaAnd.message("toString"));

                // system.message(":afficher", (Object) metaOr.message("toString"));

                // system.message(":afficher", (Object) metaNot.message("toString"));

                System.out.println(
                                "_________________________________________________________________________________________________________ Fin _____________________________________________________________________________________________________");

        }
}
