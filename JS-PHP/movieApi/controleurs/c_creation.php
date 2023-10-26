<?php

if (!isset($_GET['action'])) {
    $_GET['action'] = 'demandeCreation';
}

$action = $_GET['action'];
switch ($action) {

    case 'demandeCreation': {
            include("vues/v_creation.php");
            break;
        }

    case 'valideCreation': {
            $leLogin = htmlspecialchars($_POST['login']);
            $lePassword = htmlspecialchars($_POST['mdp']);
            $leNom = htmlspecialchars($_POST['nom']);
            $lePrenom = htmlspecialchars($_POST['prenom']);

            if ($leLogin == $_POST['login']) {
                $loginOk = true;
                $passwordOk = true;
            } else {
                echo '<h3 style="color:red; text-align:center;">Tentative d\'injection javascript - login refusé</h3>';
                $loginOk = false;
                $passwordOk = false;
            }

            $rempli = false;
            if ($loginOk && $passwordOk) {
                $rempli = true;

                if (empty($leLogin) == true) {
                    echo '<h3 style="color:red; text-align:center;">Le login n\'a pas été saisi</h3><br/>';
                    $rempli = false;
                }

                if (empty($lePassword) == true) {
                    echo '<h3 style="color:red; text-align:center;">Le mot de passe n\'a pas été saisi</h3><br/>';
                    $rempli = false;
                }

                if ($rempli) {
                    $leLogin = trim($leLogin);
                    $lePassword = trim($lePassword);

                    $nbCarMaxLogin = PdoProjet::tailleChampsMail();
                    if (strlen($leLogin) > $nbCarMaxLogin) {
                        echo '<h3 style="color:red; text-align:center;">Le login ne peut contenir plus de ' . $nbCarMaxLogin . '</h3><br/>';
                        $loginOk = false;
                    }

                    if (!filter_var($leLogin, FILTER_VALIDATE_EMAIL)) {
                        echo '<h3 style="color:red; text-align:center;">Le mail n\'a pas un format correct</h3><br/>';
                        $loginOk = false;
                    }

                    $patternPassword = '#^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*\W){12,}#';
                    if (preg_match($patternPassword, $lePassword) == false) {
                        echo '<h3 style="color:red; text-align:center;">Le mot de passe doit contenir au moins 12 caractères, une majuscule,'
                            . ' une minuscule et un caractère spécial</h3><br/>';
                        $passwordOk = false;
                    }
                }

                if ($rempli && $loginOk && $passwordOk) {
                    $executionOK = PdoProjet::creeUser($leNom, $lePrenom, $leLogin, $lePassword);

                    if ($executionOK == true) {
                        echo '<h3 style="color:red; text-align:center;">Tout est bon, votre compte a bien été créé !</h3>';
                        PdoProjet::connexionInitiale($leLogin);
                        include("vues/v_connexion.php");
                    } else {
                        echo '<h3 style="color:red; text-align:center;">Ce login existe déjà, veuillez en choisir un autre !</h3>';
                        include("vues/v_creation.php");
                    }
                }

                break;
            }
        }

    default: {
            include("vues/v_connexion.php");
            break;
        }
}
