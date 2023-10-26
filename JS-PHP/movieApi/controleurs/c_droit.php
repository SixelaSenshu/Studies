<?php

$action = $_GET['action'];
switch ($action) {

    case 'parametreCompte': {
            include("vues/v_sommaire.php");
            if ($_SESSION['id']) {
                include("vues/v_parametresCompte.php");
            }
            break;
        }

    case 'demandeModification': {
            include("vues/v_sommaire.php");
            include("vues/v_modificationCompte.php");
            break;
        }

    case 'demandeSuppression': {
            include("vues/v_sommaire.php");
            include('vues/v_supprimerCompte.php');
            break;
        }

    case 'confirmSupDef': {
            include("vues/v_sommaire.php");
            include("vues/v_confirmSupprimerCompte.php");
            break;
        }

    case 'supprimerDef': {
            $pdo = PdoProjet::getPdoPhp();
            $id = $_SESSION['id'];
            PdoProjet::SupprimerCompte($id);
            echo '<h3 style="color:red; text-align:center;">Votre compte a été supprimé !';
            include 'vues/v_connexion.php';
            break;
        }

    case 'modification': {
            include("vues/v_sommaire.php");
            $nom = $_POST['nom'];
            $prenom = $_POST['prenom'];
            $id = $_SESSION['id'];
            $mdp = htmlspecialchars($_POST['Modifmdp1']);
            $mdp2 = htmlspecialchars($_POST['Modifmdp2']);
            $rempli = false;
            if (empty($mdp) == true && empty($mdp2) == true) {
                $modifSansMdp = PdoProjet::modifNomPrenom($nom, $prenom, $id);
                echo "<h3 style='text-align:center;'>Modification effectuée !</h3>";
                $rempli = false;
                include("vues/v_connexion.php");
            } else {
                if (verif2Strings($mdp, $mdp2) == true) {
                    if (verifSecuPWP($mdp)) {
                        $modifAvecMdp = PdoProjet::modifNomPrenomMdp($nom, $prenom, $mdp, $id);
                        echo "<h3 style='text-align:center;'>Modification effectuée !</h3>";
                        include("vues/v_connexion.php");
                    }
                } else {
                    echo 'Les mots de passes ne sont pas similaires !';
                }
            }
            break;
        }
}
