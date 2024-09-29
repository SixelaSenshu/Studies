<?php

if (!isset($_GET['action'])) {
    $_GET['action'] = 'api';
}

$action = $_GET['action'];
switch ($action) {

    case 'rechercherUnFilm': {
            include("vues/v_sommaire.php");
            include("vues/v_rechercherFilm.php");
            break;
        }

    case 'recherche': {
            include("vues/v_sommaire.php");
            include("vues/v_afficheRecherche.php");
            if (isset($_POST['critereRecherche']) && isset($_POST['paramRecherche'])) {
                $critereRecherche = htmlspecialchars($_POST['critereRecherche']);
                $paramRecherche = $_POST['paramRecherche'];
            } else {
                $critereRecherche = $_GET['critereRecherche'];
                $paramRecherche = $_GET['paramRecherche'];
            }
            PdoProjet::recherche($critereRecherche, $paramRecherche);
            break;
        }

    case 'afficheRecherche': {
            include("vues/v_sommaire.php");
            include("vues/v_afficheRecherche.php");
            $idFilm = $_GET['idFilm'];
            PdoProjet::afficheInfoFilm($idFilm);
            break;
        }

    case 'noterUnFilm': {
            include("vues/v_sommaire.php");
            include("vues/v_rechercherFilm.php");
            break;
        }

    case 'noterLeFilm': {
            include("vues/v_sommaire.php");
            include("vues/v_noterFilm.php");
            break;
        }

    case 'valideNotation': {

            if (!isset($_SESSION['movieToAdd'])) {
                header("Location: index.php?uc=api&action=recherche");
                exit;
            }

            $movieToAdd = $_SESSION['movieToAdd'];
            $exec = PdoProjet::addRealisateur($movieToAdd['director_id'], $movieToAdd['director_lastname'], $movieToAdd['director_firstname'], $movieToAdd['director_birthyear']);
            $exec2 = PdoProjet::addFilm($movieToAdd['idFilm'], $movieToAdd['director_id'], $movieToAdd['idGenre1'], $movieToAdd['idGenre2'], $movieToAdd['idGenre3'], $movieToAdd['idGenre4'], $movieToAdd['title'], $movieToAdd['release_date']);
            if ($exec == true && $exec2 == true) {
                echo "<h3 style='color:red; text-align:center;'>Le film et le réalisateur enregistrés avec succès.</h3>";
                $_SESSION['movieToAdd'] = array(
                    'idFilm' => null,
                    'director_id' => null,
                    'director_lastname' => null,
                    'director_firstname' => null,
                    'director_birthyear' => null,
                    'idGenre1' => null,
                    'idGenre2' => null,
                    'idGenre3' => null,
                    'idGenre4' => null,
                    'title' => null,
                    'release_date' => null
                );
            }

            $id = $_SESSION['id'];
            $idFilm = $_POST['idFilm'];
            $note = $_POST['note'];
            $commentaire = $_POST['commentaire'];

            if (!$note && !$commentaire) {
                ajouterErreur("L'un des champs est manquant");
                include("vues/v_erreurs.php");
                include("vues/v_noterFilm.php");
            } else {
                $resultat = PdoProjet::checkNotation($id, $idFilm);
                if ($resultat === false) {
                    $exec3 = PdoProjet::ajouteNotation($id, $idFilm, $note, $commentaire);
                    $exec4 = PdoProjet::updateFilmMoyenne($idFilm);
                    if ($exec3 == true && $exec4 == true) {
                        echo "<h3 style='color:red; text-align:center;'>Note enregistrée avec succès.</h3>";
                    }
                } else {
                    echo "<h3 style='color:red; text-align:center;'>Vous avez déjà noté ce film.</h3>";
                    $exec5 = PdoProjet::modifieNotation($id, $idFilm, $note, $commentaire);
                    $exec6 = PdoProjet::updateFilmMoyenne($idFilm);
                    if ($exec5 == true && $exec6 == true) {
                        echo "<h3 style='color:red; text-align:center;'>Votre note ainsi que votre commentaire sur ce film a été modifié !</h3>";
                    }
                }
                include("vues/v_sommaire.php");
            }
            break;
        }

    case 'consulterSaListe': {
            $id = $_SESSION['id'];
            include("vues/v_sommaire.php");
            include("vues/v_maListe.php");

            $tri = isset($_GET['tri-select']) ? $_GET['tri-select'] : null;
            $ordre = isset($_GET['ordre-select']) ? $_GET['ordre-select'] : null;
            $genre = isset($_GET['genre-select']) ? $_GET['genre-select'] : null;
            $annee = isset($_GET['annee-select']) ? $_GET['annee-select'] : null;
            $realisateur = isset($_GET['realisateur-select']) ? $_GET['realisateur-select'] : null;

            $tab = PdoProjet::getListeFilmsNotesUtilisateur($id, $tri, $ordre, $genre, $annee, $realisateur);
            echo $tab;
            break;
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
