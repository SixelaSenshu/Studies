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
            <div class="col-md-4 col-md-offset-4">
                <div class="login-wrapper">
                    <div class="box">
                        <div class="content-wrap">
                            <legend>Choisissez ce que vous voulez faire : </legend>
                            <a class="btn btn-primary" href="index.php?uc=droit&action=demandeModification&id=<?php echo $_SESSION['id'] ?>">Modifier compte</a><br><br>
                            <a class="btn btn-primary" href="index.php?uc=droit&action=demandeSuppression&id=<?php echo $_SESSION['id'] ?>">Supprimer compte</a><br><br>
                            <br>
                        </div>
                    </div>
                </div>
            </div>
        </div>
</body>

</html>