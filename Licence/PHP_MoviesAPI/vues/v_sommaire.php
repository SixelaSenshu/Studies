<?php
$heure = date("h:i:s", time());
setcookie("CookieSession", $heure, 0);

if (!$_SESSION['id'])
    header('Location: ../index.php');
?>

<!DOCTYPE html>
<html lang="fr">

<head>
    <script src="https://code.jquery.com/jquery.js"></script>
    <script src="bootstrap/js/bootstrap.min.js"></script>
    <title>Projet Php</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link href="bootstrap/css/bootstrap.min.css" rel="stylesheet">
    <link href="css/styles.css" rel="stylesheet">
</head>

<body>
    <nav class="navbar navbar-default">
        <div class="container-fluid">
            <div class="navbar-header">
                <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#bs-example-navbar-collapse-1" aria-expanded="false">
                    <span class="sr-only">Navigation</span>
                </button>
                <a class="navbar-brand" href="index.php?uc=connexion&action=sommaire">Projet PHP</a>
            </div>

            <div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">
                <ul class="nav navbar-nav">
                    <li class="active"><a href="index.php?uc=api&action=rechercherUnFilm">Rechercher un film</a></li>
                    <li class="active"><a href="index.php?uc=api&action=noterUnFilm">Noter un film</a></li>
                    <li class="active"><a href="index.php?uc=api&action=consulterSaListe">Consulter sa liste</a></li>
                </ul>

                <ul class="nav navbar-nav navbar-right">
                    <li><a href="index.php?uc=droit&action=parametreCompte"><?php echo $_SESSION['prenom'] . "  " . $_SESSION['nom'] ?></a></li>
                    <li><a>User</a></li>
                    <li class="active"><a href="index.php?uc=connexion&action=demandeDeconnexion">Deconnexion</a></li>
                </ul>
            </div>
        </div>
    </nav>

    </body>

</html>