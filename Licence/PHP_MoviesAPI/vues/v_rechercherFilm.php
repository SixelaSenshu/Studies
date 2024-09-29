<?php
if (!$_SESSION['id']) {
    header('Location: ../index.php');
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
</head>

<body>
    <div class="page-content container">
        <div class="row">
            <div class="col-md-6 col-md-offset-3">
                <div class="login-wrapper">
                    <div class="box">
                        <div class="content-wrap">
                            <form method="get" action="index.php?uc=api&action=recherche&page=1">
                                <input type="hidden" name="uc" value="api">
                                <input type="hidden" name="action" value="recherche">
                                <label for="film_title">Rechercher un film par
                                    <select name="critereRecherche" id="critereRecherche">
                                        <option value="name" selected="selected">nom de film</option>
                                        <option value="actor">acteur</option>
                                        <option value="genre">genre</option>
                                    </select>
                                    :
                                </label>
                                <br><br>

                                <div id="input-container">
                                    <input type="text" name="paramRecherche" placeholder="Rechercher un film, un genre, un artiste, ..." size="50" style="text-align: center;" required>
                                </div>
                                <br>
                                <input type="hidden" name="page" value="1">
                                <input type="submit" value="Rechercher">
                            </form>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>

    <script>
        var critereRecherche = document.getElementById('critereRecherche');
        var inputContainer = document.getElementById('input-container');
        var select;

        critereRecherche.addEventListener('change', function() {
            if (critereRecherche.value === 'genre') {
                select = document.createElement('select');
                select.name = 'paramRecherche';
                select.style.textAlign = 'center';
                select.required = true;

                var option1 = document.createElement('option');
                option1.value = '';
                option1.text = 'Sélectionnez un genre';
                select.appendChild(option1);

                <?php
                $genres_results = PdoProjet::getListeGenre();
                foreach ($genres_results['genres'] as $genre) {
                    echo 'var option = document.createElement(\'option\');
                    option.value = \'' . $genre['id'] . '\';
                    option.text = \'' . $genre['name'] . '\';
                    select.appendChild(option);';
                }
                ?>

                inputContainer.innerHTML = '';
                inputContainer.appendChild(select);
                document.getElementById('input-text').style.display = 'none';
            } else {
                var input = document.createElement('input');
                input.id = 'input-text';
                input.type = 'text';
                input.name = 'paramRecherche';
                input.placeholder = 'Rechercher un film, un genre, un artiste, ...';
                input.size = '50';
                input.style.textAlign = 'center';
                input.required = true;

                inputContainer.innerHTML = '';
                inputContainer.appendChild(input);
                if (select) {
                    select.style.display = 'none';
                }
            }
        });
    </script>

</body>

</html>