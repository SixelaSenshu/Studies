<!DOCTYPE html>
<html lang="fr">

<head>
    <title>GSB -extranet</title>
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
                            <legend>Je souhaite créer un compte</legend>
                            <form method="post" action="index.php?uc=creation&action=valideCreation">
                                <input name="login" class="form-control" type="email" placeholder="mail" />
                                <input name="mdp" class="form-control" type="password" placeholder="password" />
                                <input name="prenom" class="form-control" type="text" placeholder="prénom" />
                                <input name="nom" class="form-control" type="text" placeholder="nom" />
                                <br><br>
                                <input type="submit" class="btn btn-primary signup" value="Créer" />
                            </form>
                            <br>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>

    <script src="https://code.jquery.com/jquery.js"></script>
    <script src="bootstrap/js/bootstrap.min.js"></script>
    <script src="js/custom.js"></script>
</body>

</html>