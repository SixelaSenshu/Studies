<?php
$genres_options = "<option value='' selected>-- Sélectionnez --</option>";
$genres_results = PdoProjet::getListeGenresFilmsNotesUtilisateur($_SESSION['id']);
foreach ($genres_results as $genre) {
    $genres_options .= "<option value='$genre'>$genre</option>";
}

$annees_options = "<option value='' selected>-- Sélectionnez --</option>";
$annees_results = PdoProjet::getListeAnneesSortieFilmsNotesUtilisateur($_SESSION['id']);
foreach ($annees_results as $annee) {
    $annees_options .= "<option value='$annee'>$annee</option>";
}

$realisateurs_options = "<option value='' selected>-- Sélectionnez --</option>";
$realisateurs_results = PdoProjet::getListeRealisateursFilmsNotesUtilisateur($_SESSION['id']);
foreach ($realisateurs_results as $realisateur) {
    $realisateurs_options .= "<option value='$realisateur'>$realisateur</option>";
}
?>

<!DOCTYPE html>
<html lang="fr">

<head>
    <script src="https://code.jquery.com/jquery.js"></script>
    <script src="bootstrap/js/bootstrap.min.js"></script>
    <title>Projet PHP</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link href="bootstrap/css/bootstrap.min.css" rel="stylesheet">
    <link href="css/styles.css" rel="stylesheet">
    <link href="css/list.css" rel="stylesheet">
</head>

<body>

    <center>
        <div class ="maListe">
        <div class ="maListe-select">
        <div class ="maListe-select-header">
        <form action='index.php?uc=api&action=consulterSaListe' method="get" onsubmit="replaceEmptyWithNull()">
            <input type="hidden" name="uc" value="api">
            <input type="hidden" name="action" value="consulterSaListe">
            <label for="tri-select">Tri :</label>
            <select name="tri-select" id="tri-select">
                <option value="">-- Sélectionnez --</option>
                <option value="nomFilm">Nom film</option>
                <option value="moyenne">Moyenne</option>
            </select>

            <label for="ordre-select">Ordre :</label>
            <select name="ordre-select" id="ordre-select">
                <option value="">-- Sélectionnez --</option>
                <option value="asc">Croissant</option>
                <option value="desc">Décroissant</option>
            </select>

            <label for="filtre-select">Filtrer par :</label>
            <select id="filtre-select" name="filtre-select">
                <option value="">-- Sélectionnez --</option>
                <option value="genre">Genre</option>
                <option value="annee">Année</option>
                <option value="realisateur">Réalisateur</option>
            </select>
            </div>
            <div class ="maListe-select-header">
            <label for="genre-select">Genre :</label>
            <select id="genre-select" name="genre-select" disabled>
                <?php echo $genres_options; ?>
            </select>

            <label for="annee-select">Année :</label>
            <select id="annee-select" name="annee-select" disabled>
                <?php echo $annees_options; ?>
            </select>

            <label for="realisateur-select">Réalisateur :</label>
            <select id="realisateur-select" name="realisateur-select" disabled>
                <?php echo $realisateurs_options; ?>
            </select>
            </div>
            <br>
            </div>
            <button type="submit">Valider</button>
        </form>
        </div>  
    </center>

    <script>
        const filtreSelect = document.getElementById("filtre-select");
        const genreSelect = document.getElementById("genre-select");
        const anneeSelect = document.getElementById("annee-select");
        const realisateurSelect = document.getElementById("realisateur-select");

        genreSelect.disabled = true;
        anneeSelect.disabled = true;
        realisateurSelect.disabled = true;

        filtreSelect.addEventListener("change", function() {
            if (this.value === "genre") {
                genreSelect.disabled = false;
                anneeSelect.disabled = true;
                realisateurSelect.disabled = true;
            } else if (this.value === "annee") {
                genreSelect.disabled = true;
                anneeSelect.disabled = false;
                realisateurSelect.disabled = true;
            } else if (this.value === "realisateur") {
                genreSelect.disabled = true;
                anneeSelect.disabled = true;
                realisateurSelect.disabled = false;
            } else {
                genreSelect.disabled = true;
                anneeSelect.disabled = true;
                realisateurSelect.disabled = true;
            }
        });

        function replaceEmptyWithNull() {
            var form = document.querySelector('form');
            var inputs = form.querySelectorAll('input, select');
            for (var i = 0; i < inputs.length; i++) {
                if (inputs[i].value.trim() === '') {
                    inputs[i].value = null;
                }
            }
        }
    </script>

</body>

</html>