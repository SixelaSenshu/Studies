<?php
if (!$_SESSION['id'])
    header('Location: ../index.php');
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
                            <legend>Modifier vos informations : </legend>
                            <form method="post" action="index.php?uc=droit&action=modification">
                                <p style='font-size:15px'>Entrer votre nouveau Mot de Passe :</p>
                                <input name="Modifmdp1" class="form-control" type="password" placeholder="Entrer votre nouveau mot de passe ici !" /><br>
                                <input name="Modifmdp2" class="form-control" type="password" placeholder="Confirmer votre mot de passe ici !" />
                                <br><br>
                                <p style='font-size:15px'>Entrer votre nouveau prénom : </p>
                                <input name="prenom" class="form-control" type="text" value="<?php echo $_SESSION['prenom']; ?>" />

                                <p style='font-size:15px'>Entrer votre nouveau nom : </p>
                                <input name="nom" class="form-control" type="text" value="<?php echo $_SESSION['nom']; ?>" />
                                <input type="submit" class="btn btn-primary signup" value="Valider" /><br><br>
                            </form>
                            <br>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>
</body>

</html>