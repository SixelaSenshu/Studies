<!DOCTYPE html>
<html lang="fr">

<head>
    <script src="https://code.jquery.com/jquery.js"></script>
    <script src="bootstrap/js/bootstrap.min.js"></script>
    <title>Projet PHP</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link href="bootstrap/css/bootstrap.min.css" rel="stylesheet">
    <link href="css/styles.css" rel="stylesheet">
    <link href="css/search.css" rel="stylesheet">
</head>

<body>
    <?php $id_film = $_GET['idFilm']; ?>
    <div class="box">
        <div class="pagination">
            <form method="POST" action="index.php?uc=api&action=valideNotation">
                <input type="hidden" name="idFilm" value="<?php echo $id_film; ?>">
                <div>
                    <label for="note">Note :</label>
                    <select name="note" id="note">
                        <option value="1">1 étoile</option>
                        <option value="2">2 étoiles</option>
                        <option value="3">3 étoiles</option>
                        <option value="4">4 étoiles</option>
                        <option value="5">5 étoiles</option>
                    </select>
                </div>
                <div>
                    <label for="commentaire">Commentaire :</label>
                    <textarea name="commentaire" id="commentaire" maxlength="300" minlength="5" rows="20" cols="120"></textarea>
                </div>
                <br>
                <div>
                    <button type="submit">Envoyer</button>
                </div>
            </form>
        </div>
    </div>
</body>

</html>