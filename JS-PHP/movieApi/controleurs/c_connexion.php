<?php

if (!isset($_GET['action'])) {
    $_GET['action'] = 'demandeConnexion';
}

$action = $_GET['action'];
switch ($action) {

    case 'demandeConnexion': {
            include("vues/v_connexion.php");
            break;
        }

    case 'valideConnexion': {
            $login = $_POST['login'];
            $mdp = $_POST['mdp'];
            $connexionOk = PdoProjet::checkUser($login, $mdp);

            if (!$connexionOk) {
                ajouterErreur("Login ou mot de passe incorrect");
                include("vues/v_erreurs.php");
                include("vues/v_connexion.php");
            } else {
                $infosUser = PdoProjet::donneLeUserByMail($login);
                $id = $infosUser['id'];
                $nom =  $infosUser['nom'];
                $prenom = $infosUser['prenom'];
                connecter($id, $nom, $prenom);
                $connection = PdoProjet::ajouteConnexion($id);
                include("vues/v_sommaire.php");
            }
            break;
        }

    case 'demandeDeconnexion': {

            if ($_COOKIE["CookieSession"] == null) {
                header('Location:index.php');
            } else {
                $id = $_SESSION['id'];
                $deco = PdoProjet::ajouteDeconnexion($id);
                $heure2 = strtotime(date("h:i:s"), time());
                $heureCookie = strtotime($_COOKIE["CookieSession"]);
                $tempsRester = $heure2 - $heureCookie;
                $message = '<h3 style="color:red; text-align:center;">Vous êtes resté ' . $tempsRester . ' secondes sur notre site</h3>';
                echo $message;
                setcookie("CookieSession");
                include("vues/v_connexion.php");
                break;
            }
        }

    case 'sommaire': {
            include("vues/v_sommaire.php");
            break;
        }

    default: {
            include("vues/v_connexion.php");
            break;
        }
}
