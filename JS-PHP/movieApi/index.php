<?php

require_once("include/fct.inc.php");
require_once("include/PdoProjet.php");
session_start();

date_default_timezone_set('Europe/Paris');

$pdo = PdoProjet::getPdoPhp();
$estConnecte = estConnecte();

PdoProjet::createUserTable('users');
PdoProjet::createHistoriqueConnexionTable('historiqueConnexion');
PdoProjet::createRealisateurTable('realisateur');
PdoProjet::createNotationTable('notation');
PdoProjet::createFilmsTable('films');
PdoProjet::createGenreTable('genres');

if (!isset($_GET['uc'])) {
    $_GET['uc'] = 'connexion';
} else {
    if ($_GET['uc'] == "connexion" && !estConnecte()) {
        $_GET['uc'] = 'connexion';
    }
}

$uc = $_GET['uc'];
switch ($uc) {
    case 'connexion': {
            include("controleurs/c_connexion.php");
            break;
        }

    case 'creation': {
            include("controleurs/c_creation.php");
            break;
        }

    case 'droit': {
            include("controleurs/c_droit.php");
            break;
        }

    case 'api': {
            include("controleurs/c_api.php");
            break;
        }
}
